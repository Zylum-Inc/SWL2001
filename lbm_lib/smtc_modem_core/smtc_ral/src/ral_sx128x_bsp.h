/**
 * @file      ral_sx128x_bsp.h
 *
 * @brief     Board Support Package for the SX128x-specific RAL.
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RAL_SX128X_BSP_H
#define RAL_SX128X_BSP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include "ral_defs.h"
#include "sx128x.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

typedef struct ral_sx128x_bsp_tx_cfg_input_params_s
{
    int8_t   system_output_pwr_in_dbm;
    uint32_t freq_in_hz;
} ral_sx128x_bsp_tx_cfg_input_params_t;

typedef struct ral_sx128x_bsp_tx_cfg_output_params_s
{
    sx128x_ramp_time_t pa_ramp_time;
    int8_t             chip_output_pwr_in_dbm_configured;
    int8_t             chip_output_pwr_in_dbm_expected;
} ral_sx128x_bsp_tx_cfg_output_params_t;

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/**
 * Get the regulator mode configuration
 *
 * @param [in] context Chip implementation context
 * @param [out] reg_mode
 */
void ral_sx128x_bsp_get_reg_mode( const void* context, sx128x_reg_mod_t* reg_mode );

/**
 * Get the Tx-related configuration (power amplifier configuration, output power and ramp time) to be applied to the
 * chip
 *
 * @param [in] context Chip implementation context
 * @param [in] input_params Parameters used to compute the chip configuration
 * @param [out] output_params Parameters to be configured in the chip
 */
void ral_sx128x_bsp_get_tx_cfg( const void* context, const ral_sx128x_bsp_tx_cfg_input_params_t* input_params,
                                ral_sx128x_bsp_tx_cfg_output_params_t* output_params );

/**
 * @brief Get the Channel Activity Detection (CAD) DetPeak value
 *
 * @param [in] context Chip implementation context
 * @param [in] sf                       CAD LoRa spreading factor
 * @param [in] bw                       CAD LoRa bandwidth
 * @param [in] nb_symbol                CAD on number of symbols
 * @param [in out] in_out_cad_det_peak  CAD DetPeak value proposed by the ral could be overwritten
 */
void ral_sx128x_bsp_get_lora_cad_det_peak( const void* context, ral_lora_sf_t sf, ral_lora_bw_t bw,
                                           ral_lora_cad_symbs_t nb_symbol, uint8_t* in_out_cad_det_peak );

/**
 * @brief Get the instantaneous power consumption for the given Tx configuration
 *
 * @param [in] context Chip implementation context
 * @param [in] tx_cfg_output_params_local The Tx configuration
 * @param [in] reg_mode The regulator configuration
 * @param [out] pwr_consumption_in_ua The corresponding instantaneous power consumption
 * @return ral_status_t
 */
ral_status_t ral_sx128x_bsp_get_instantaneous_tx_power_consumption(const void* context,
    ral_sx128x_bsp_tx_cfg_output_params_t tx_cfg_output_params_local, sx128x_reg_mod_t reg_mode,
    uint32_t* pwr_consumption_in_ua );

/**
 * @brief Get the instantaneous power consumption for the given GFSK Rx configuration
 *
 * @param [in] context Chip implementation context
 * @param [in] radio_reg_mode The regulator configuration
 * @param [in] rx_boosted The Rx boosted configuration
 * @param [out] pwr_consumption_in_ua The corresponding instantaneous power consumption
 * @return ral_status_t
 */
ral_status_t ral_sx128x_bsp_get_instantaneous_gfsk_rx_power_consumption( const void* context,
    sx128x_reg_mod_t radio_reg_mode, bool rx_boosted, uint32_t* pwr_consumption_in_ua );

/**
 * @brief Get the instantaneous power consumption for the given LoRa Rx configuration
 *
 * @param [in] context Chip implementation context
 * @param [in] reg_mode The regulator configuration
 * @param [in] bw The LoRa bandwidth configured
 * @param [in] rx_boosted The Rx boosted configuration
 * @param [out] pwr_consumption_in_ua The corresponding instantaneous power consumption
 * @return ral_status_t
 */
ral_status_t ral_sx128x_bsp_get_instantaneous_lora_rx_power_consumption( const void* context,
    sx128x_reg_mod_t reg_mode, ral_lora_bw_t bw, bool rx_boosted, uint32_t* pwr_consumption_in_ua );

#ifdef __cplusplus
}
#endif

#endif  // RAL_SX128X_BSP_H

/* --- EOF ------------------------------------------------------------------ */
