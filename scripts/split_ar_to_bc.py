#!/usr/bin/env python3
import argparse, subprocess, os, sys, tempfile, shutil

BITCODE_MAGICS = (b'BC\xc0\xde', b'\x0b\x17\xc0\xde')  # raw + wrapper

def is_bitcode(p):
    try:
        with open(p, 'rb') as f:
            h = f.read(4)
        return h in BITCODE_MAGICS
    except Exception:
        return False

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--archive', required=True)
    ap.add_argument('--out-bc', required=True)
    ap.add_argument('--out-native', required=True)
    ap.add_argument('--llvm-ar', required=True)
    ap.add_argument('--llvm-link', required=True)
    ap.add_argument('--workdir', default=None)
    args = ap.parse_args()

    tmp = args.workdir or tempfile.mkdtemp(prefix='split_ar_')
    os.makedirs(tmp, exist_ok=True)

    # List members and extract all
    res = subprocess.run([args.llvm_ar, 't', args.archive],
                         check=True, capture_output=True, text=True)
    members = [m.strip() for m in res.stdout.splitlines() if m.strip()]
    subprocess.run([args.llvm_ar, 'x', args.archive], check=True, cwd=tmp)

    bc, native = [], []
    for m in members:
        # llvm-ar extracts under the member name (sometimes with dirs)
        cand = os.path.join(tmp, m)
        if not os.path.exists(cand):
            cand = os.path.join(tmp, os.path.basename(m))
        if not os.path.exists(cand):
            print(f'warning: missing member after extract: {m}', file=sys.stderr)
            continue
        (bc if is_bitcode(cand) else native).append(cand)

    if not bc:
        print('error: no bitcode members found in archive', file=sys.stderr)
        return 2

    # Link bitcode into a single .bc
    out_bc_tmp = args.out_bc + '.tmp'
    subprocess.run([args.llvm_link, '-o', out_bc_tmp] + bc, check=True)
    os.replace(out_bc_tmp, args.out_bc)

    # Pack native members (if any) into a separate .a
    if native:
        if os.path.exists(args.out_native):
            os.remove(args.out_native)
        subprocess.run([args.llvm_ar, 'rcsD', args.out_native] + native, check=True)
    else:
        # Ensure the output exists even if empty (optional)
        open(args.out_native, 'wb').close()

    # Clean temp if we created it
    if args.workdir is None:
        shutil.rmtree(tmp, ignore_errors=True)
    return 0

if __name__ == '__main__':
    sys.exit(main())
