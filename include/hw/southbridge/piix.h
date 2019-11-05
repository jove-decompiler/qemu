/*
 * QEMU PIIX South Bridge Emulation
 *
 * Copyright (c) 2006 Fabrice Bellard
 * Copyright (c) 2018 Hervé Poussineau
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef HW_SOUTHBRIDGE_PIIX_H
#define HW_SOUTHBRIDGE_PIIX_H

#define TYPE_PIIX4_PM "PIIX4_PM"

I2CBus *piix4_pm_init(PCIBus *bus, int devfn, uint32_t smb_io_base,
                      qemu_irq sci_irq, qemu_irq smi_irq,
                      int smm_enabled, DeviceState **piix4_pm);

extern PCIDevice *piix4_dev;

DeviceState *piix4_create(PCIBus *pci_bus, ISABus **isa_bus,
                          I2CBus **smbus, size_t ide_buses);

#endif
