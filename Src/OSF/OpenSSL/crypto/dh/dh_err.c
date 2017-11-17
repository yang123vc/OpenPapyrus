/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */
#include "internal/cryptlib.h"
#pragma hdrstop
//#include <openssl/err.h>
#include <openssl/dh.h>

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

#define ERR_FUNC(func) ERR_PACK(ERR_LIB_DH,func,0)
#define ERR_REASON(reason) ERR_PACK(ERR_LIB_DH,0,reason)

static ERR_STRING_DATA DH_str_functs[] = {
    {ERR_FUNC(DH_F_COMPUTE_KEY), "compute_key"},
    {ERR_FUNC(DH_F_DHPARAMS_PRINT_FP), "DHparams_print_fp"},
    {ERR_FUNC(DH_F_DH_BUILTIN_GENPARAMS), "dh_builtin_genparams"},
    {ERR_FUNC(DH_F_DH_CMS_DECRYPT), "dh_cms_decrypt"},
    {ERR_FUNC(DH_F_DH_CMS_SET_PEERKEY), "dh_cms_set_peerkey"},
    {ERR_FUNC(DH_F_DH_CMS_SET_SHARED_INFO), "dh_cms_set_shared_info"},
    {ERR_FUNC(DH_F_DH_METH_DUP), "DH_meth_dup"},
    {ERR_FUNC(DH_F_DH_METH_NEW), "DH_meth_new"},
    {ERR_FUNC(DH_F_DH_METH_SET1_NAME), "DH_meth_set1_name"},
    {ERR_FUNC(DH_F_DH_NEW_METHOD), "DH_new_method"},
    {ERR_FUNC(DH_F_DH_PARAM_DECODE), "dh_param_decode"},
    {ERR_FUNC(DH_F_DH_PRIV_DECODE), "dh_priv_decode"},
    {ERR_FUNC(DH_F_DH_PRIV_ENCODE), "dh_priv_encode"},
    {ERR_FUNC(DH_F_DH_PUB_DECODE), "dh_pub_decode"},
    {ERR_FUNC(DH_F_DH_PUB_ENCODE), "dh_pub_encode"},
    {ERR_FUNC(DH_F_DO_DH_PRINT), "do_dh_print"},
    {ERR_FUNC(DH_F_GENERATE_KEY), "generate_key"},
    {ERR_FUNC(DH_F_PKEY_DH_DERIVE), "pkey_dh_derive"},
    {ERR_FUNC(DH_F_PKEY_DH_KEYGEN), "pkey_dh_keygen"},
    {0, NULL}
};

static ERR_STRING_DATA DH_str_reasons[] = {
    {ERR_REASON(DH_R_BAD_GENERATOR), "bad generator"},
    {ERR_REASON(DH_R_BN_DECODE_ERROR), "bn decode error"},
    {ERR_REASON(DH_R_BN_ERROR), "bn error"},
    {ERR_REASON(DH_R_DECODE_ERROR), "decode error"},
    {ERR_REASON(DH_R_INVALID_PUBKEY), "invalid public key"},
    {ERR_REASON(DH_R_KDF_PARAMETER_ERROR), "kdf parameter error"},
    {ERR_REASON(DH_R_KEYS_NOT_SET), "keys not set"},
    {ERR_REASON(DH_R_MODULUS_TOO_LARGE), "modulus too large"},
    {ERR_REASON(DH_R_NO_PARAMETERS_SET), "no parameters set"},
    {ERR_REASON(DH_R_NO_PRIVATE_VALUE), "no private value"},
    {ERR_REASON(DH_R_PARAMETER_ENCODING_ERROR), "parameter encoding error"},
    {ERR_REASON(DH_R_PEER_KEY_ERROR), "peer key error"},
    {ERR_REASON(DH_R_SHARED_INFO_ERROR), "shared info error"},
    {0, NULL}
};

#endif

int ERR_load_DH_strings(void)
{
#ifndef OPENSSL_NO_ERR

    if (ERR_func_error_string(DH_str_functs[0].error) == NULL) {
        ERR_load_strings(0, DH_str_functs);
        ERR_load_strings(0, DH_str_reasons);
    }
#endif
    return 1;
}