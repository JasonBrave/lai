/*
 * Lightweight ACPI Implementation
 * Copyright (C) 2018-2020 the lai authors
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// FADT Event/Status Fields
#define ACPI_TIMER            0x0001
#define ACPI_BUSMASTER            0x0010
#define ACPI_GLOBAL            0x0020
#define ACPI_POWER_BUTTON        0x0100
#define ACPI_SLEEP_BUTTON        0x0200
#define ACPI_RTC_ALARM            0x0400
#define ACPI_PCIE_WAKE            0x4000
#define ACPI_WAKE            0x8000

// FADT Control Block
#define ACPI_ENABLED            0x0001
#define ACPI_SLEEP            0x2000

#define ACPI_GAS_MMIO          0x00
#define ACPI_GAS_IO            0x01
#define ACPI_GAS_PCI           0x02
#define ACPI_GAS_EC            0x03
#define ACPI_GAS_SMBUS         0x04
#define ACPI_GAS_CMOS          0x05
#define ACPI_GAS_PCIBAR        0x06
#define ACPI_GAS_IPMI          0x07
#define ACPI_GAS_GPIO          0x08
#define ACPI_GAS_SERIAL        0x09
#define ACPI_GAS_PCC           0x0a

// OpRegion Address Spaces
#define ACPI_OPREGION_MEMORY			0x00
#define ACPI_OPREGION_IO			0x01
#define ACPI_OPREGION_PCI			0x02
#define ACPI_OPREGION_EC			0x03
#define ACPI_OPREGION_SMBUS			0x04
#define ACPI_OPREGION_CMOS			0x05
#define ACPI_OPREGION_OEM			0x80

typedef struct acpi_rsdp_t
{
    char signature[8];
    uint8_t checksum;
    char oem[6];
    uint8_t revision;
    uint32_t rsdt;
}__attribute__((packed)) acpi_rsdp_t;

typedef struct acpi_xsdp_t
{
    char signature[8];
    uint8_t checksum;
    char oem[6];
    uint8_t revision;
    uint32_t rsdt;
    uint32_t length;
    uint64_t xsdt;
    uint8_t extended_checksum;
}__attribute__((packed)) acpi_xsdp_t;

typedef struct acpi_header_t
{
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oem[6];
    char oem_table[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
}__attribute__((packed)) acpi_header_t;

typedef struct acpi_rsdt_t
{
    acpi_header_t header;
    uint32_t tables[];
}__attribute__((packed)) acpi_rsdt_t;

typedef struct acpi_xsdt_t
{
    acpi_header_t header;
    uint64_t tables[];
}__attribute__((packed)) acpi_xsdt_t;

typedef struct acpi_gas_t
{
    uint8_t address_space;
    uint8_t bit_width;
    uint8_t bit_offset;
    uint8_t access_size;
    uint64_t base;
}__attribute__((packed)) acpi_gas_t;

typedef struct acpi_fadt_t
{
    acpi_header_t header;
    uint32_t firmware_control;
    uint32_t dsdt;        // pointer to dsdt

    uint8_t reserved;

    uint8_t profile;
    uint16_t sci_irq;
    uint32_t smi_command_port;
    uint8_t acpi_enable;
    uint8_t acpi_disable;
    uint8_t s4bios_req;
    uint8_t pstate_control;
    uint32_t pm1a_event_block;
    uint32_t pm1b_event_block;
    uint32_t pm1a_control_block;
    uint32_t pm1b_control_block;
    uint32_t pm2_control_block;
    uint32_t pm_timer_block;
    uint32_t gpe0_block;
    uint32_t gpe1_block;
    uint8_t pm1_event_length;
    uint8_t pm1_control_length;
    uint8_t pm2_control_length;
    uint8_t pm_timer_length;
    uint8_t gpe0_length;
    uint8_t gpe1_length;
    uint8_t gpe1_base;
    uint8_t cstate_control;
    uint16_t worst_c2_latency;
    uint16_t worst_c3_latency;
    uint16_t flush_size;
    uint16_t flush_stride;
    uint8_t duty_offset;
    uint8_t duty_width;

    // cmos registers
    uint8_t day_alarm;
    uint8_t month_alarm;
    uint8_t century;

    // ACPI 2.0 fields
    uint16_t iapc_boot_flags;
    uint8_t reserved2;
    uint32_t flags;

    acpi_gas_t reset_register;
    uint8_t reset_command;
    uint16_t arm_boot_flags;
    uint8_t minor_version;

    uint64_t x_firmware_control;
    uint64_t x_dsdt;

    acpi_gas_t x_pm1a_event_block;
    acpi_gas_t x_pm1b_event_block;
    acpi_gas_t x_pm1a_control_block;
    acpi_gas_t x_pm1b_control_block;
    acpi_gas_t x_pm2_control_block;
    acpi_gas_t x_pm_timer_block;
    acpi_gas_t x_gpe0_block;
    acpi_gas_t x_gpe1_block;

	acpi_gas_t sleep_control_reg;
	acpi_gas_t sleep_status_reg;
	uint64_t hypervisor_vendor;
}__attribute__((packed)) acpi_fadt_t;

#define ACPI_FADT_FLAGS_WBINVD (1 << 0)
#define ACPI_FADT_FLAGS_WBINVD_FLUSH (1 << 1)
#define ACPI_FADT_FLAGS_PROC_C1 (1 << 2)
#define ACPI_FADT_FLAGS_P_LVL2_UP (1 << 3)
#define ACPI_FADT_FLAGS_PWR_BUTTON (1 << 4)
#define ACPI_FADT_FLAGS_SLP_BUTTON (1 << 5)
#define ACPI_FADT_FLAGS_FIX_RTC (1 << 6)
#define ACPI_FADT_FLAGS_RTC_S4 (1 << 7)
#define ACPI_FADT_FLAGS_TMR_VAL_EXT (1 << 8)
#define ACPI_FADT_FLAGS_DCK_CAP (1 << 9)
#define ACPI_FADT_FLAGS_RESET_REG_SUP (1 << 10)
#define ACPI_FADT_FLAGS_SEALED_CASE (1 << 11)
#define ACPI_FADT_FLAGS_HEADLESS (1 << 12)
#define ACPI_FADT_FLAGS_CPU_SW_SLP (1 << 13)
#define ACPI_FADT_FLAGS_PCI_EXP_WAK (1 << 14)
#define ACPI_FADT_FLAGS_USE_PLATFORM_CLOCK (1 << 15)
#define ACPI_FADT_FLAGS_S4_RTC_STS_VALID (1 << 16)
#define ACPI_FADT_FLAGS_REMOTE_POWER_ON_CAPABLE (1 << 17)
#define ACPI_FADT_FLAGS_FORCE_APIC_CLUSTER_MODEL (1 << 18)
#define ACPI_FADT_FLAGS_FORCE_APIC_PHYSICAL_DESTINATION_MODE (1 << 19)
#define ACPI_FADT_FLAGS_HW_REDUCED_ACPI (1 << 20)
#define ACPI_FADT_FLAGS_LOW_POWER_S0_IDLE_CAPABLE (1 << 21)

#define ACPI_FADT_IAPC_BOOT_FLAGS_LEGACY_DEVICES (1 << 0)
#define ACPI_FADT_IAPC_BOOT_FLAGS_8042 (1 << 1)
#define ACPI_FADT_IAPC_BOOT_FLAGS_VGA_NOT_PRESENT (1 << 2)
#define ACPI_FADT_IAPC_BOOT_FLAGS_MSI_NOT_SUPPORTED (1 << 3)
#define ACPI_FADT_IAPC_BOOT_FLAGS_PCIE_ASPM_CONTROLS (1 << 4)
#define ACPI_FADT_IAPC_BOOT_FLAGS_CMOS_RTC_NOT_PRESENT (1 << 5)

typedef struct acpi_ecdt_t {
    acpi_header_t header;
    acpi_gas_t ec_control;
    acpi_gas_t ec_data;
    uint32_t uid;
    uint8_t gpe_bit;
    uint8_t ec_id[];
}__attribute__((packed)) acpi_ecdt_t;

typedef struct acpi_aml_t        // AML tables, DSDT and SSDT
{
    acpi_header_t header;
    uint8_t data[];
}__attribute__((packed)) acpi_aml_t;

#ifdef __cplusplus
}
#endif
