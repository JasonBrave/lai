/*
 * Lightweight ACPI Implementation
 * Copyright (C) 2018-2019 the lai authors
 */

#pragma once

// Embedded Controller Commands
#define ACPI_EC_READ           0x80
#define ACPI_EC_WRITE          0x81
#define ACPI_EC_BURST_ENABLE   0x82
#define ACPI_EC_BURST_DISABLE  0x83
#define ACPI_EC_QUERY          0x84

// Embedded Controller Status Flags
#define ACPI_EC_STATUS_OBF     0 // Output buffer full
#define ACPI_EC_STATUS_IBF     1 // Input buffer full
#define ACPI_EC_STATUS_CMD     3 // Internally used
#define ACPI_EC_STATUS_BURST   4 // Temporarily halts normal processing so multiple commands can be processed
#define ACPI_EC_STATUS_SCI_EVT 5 // SCI event pending
#define ACPI_EC_STATUS_SMI_EVT 6 // SMI event pending