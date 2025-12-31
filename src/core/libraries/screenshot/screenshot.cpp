// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/logging/log.h"
#include "core/libraries/error_codes.h"
#include "core/libraries/libs.h"
#include "screenshot.h"
#include "core/libraries/libc_internal/printf.h"
#include "common/va_ctx.h"

//TODO IGNORE FILE

namespace Libraries::ScreenShot {

int PS4_SYSV_ABI _Z5dummyv() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotCapture() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotDisable() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotDisableNotification() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotEnable() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotEnableNotification() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotGetAppInfo() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotGetDrcParam() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotIsDisabled() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotIsVshScreenCaptureDisabled() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotSetOverlayImage() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotSetOverlayImageWithOrigin() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotSetParam() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI sceScreenShotSetDrcParam() {
    LOG_ERROR(Lib_Screenshot, "(STUBBED) called");
    return ORBIS_OK;
}

int PS4_SYSV_ABI _printf(VA_ARGS) {
    VA_CTX(ctx);
    return LibcInternal::printf_ctx(&ctx);
}

int PS4_SYSV_ABI _sprintf(char* buff, VA_ARGS) {
    VA_CTX(ctx);
    auto result = LibcInternal::snprintf_ctx(buff, 0x1000, &ctx);

    LOG_CRITICAL(Lib_Screenshot, "sp: {}", buff);

    return result;
}

int PS4_SYSV_ABI _snprintf(char* buff, size_t len, VA_ARGS) {
    VA_CTX(ctx);
    auto result = LibcInternal::snprintf_ctx(buff, len, &ctx);

    LOG_CRITICAL(Lib_Screenshot, "snp: {}", buff);

    return result;
}

int PS4_SYSV_ABI _vsnprintf(char* buff, size_t len, char* fmt, VA_ARGS) {
    VA_CTX(ctx);
    //auto result = LibcInternal::snprintf_ctx(buff, len, &ctx);

    LOG_CRITICAL(Lib_Screenshot, "snp: {}", fmt);

    return 0;
}

const char* str = "_ServerTimeGet"; 

int PS4_SYSV_ABI _strlen(char* buff) {
    // auto result = LibcInternal::snprintf_ctx(buff, len, &ctx);

    if (buff) {
    
        if (strstr(buff, str) != nullptr) {
            LOG_CRITICAL(Lib_Screenshot, "len: {}", 64);

        }


        //LOG_CRITICAL(Lib_Screenshot, "len: {}", buff);
    }


    return strlen(buff);
}


//TODO move in a proper place
int PS4_SYSV_ABI sceNpSignalingCreateContext(s32 one, void* two, void* three, s32* context_id) {


    static int context_id_counter = 0;
    *context_id = ++context_id_counter;

    return ORBIS_OK;
}

int PS4_SYSV_ABI sceNpLookupCreateTitleCtx(void* one) {

    
    return 1;
}
// ----------

//npServiceLabel : Integer; selfNpId : PSceNpId

std::string WcharToString(wchar_t* wstr) {
    if (!wstr)
        return "";

    std::mbstate_t state = std::mbstate_t();

    // 1. Calculate Length
    // Pass a copy of the pointer because wcsrtombs moves it
    const wchar_t* src_copy = wstr;
    size_t len = std::wcsrtombs(nullptr, &src_copy, 0, &state);

    // 2. CHECK FOR ERROR (This is where you crashed before)
    if (len == static_cast<size_t>(-1)) {
        return "<invalid_wide_string>";
    }

    // 3. Allocate (len + 1 for null terminator)
    std::vector<char> mbstr(len + 1);

    // 4. Convert
    src_copy = wstr; // Reset pointer for second pass
    std::wcsrtombs(&mbstr[0], &src_copy, mbstr.size(), &state);

    return std::string(mbstr.data());
}

bool print = false;

//wcslen
int PS4_SYSV_ABI _wcstrlen(wchar_t* buff) {
    // auto result = LibcInternal::snprintf_ctx(buff, len, &ctx);

    if (print) {

        std::string ws = WcharToString(buff);
        LOG_CRITICAL(Lib_Screenshot, "wcs: {}", ws);
    }
    return wcslen(buff);
}

int PS4_SYSV_ABI _swprintf(wchar_t* buffer,     // 1. Destination Buffer
                           size_t sizeOfBuffer, // 2. Maximum Count (Capacity)
                           const wchar_t* format, 
                            VA_ARGS) {
    VA_CTX(ctx);
    
    char* cStr = &WcharToString(buffer)[0];
    auto cFrmt = WcharToString(const_cast<wchar_t*>(format)).data();

    auto result = LibcInternal::vsnprintf_ctx(cStr, sizeOfBuffer, cFrmt, &ctx.va_list);

    LOG_CRITICAL(Lib_Screenshot, "sp: {}", cStr);

    return result;
}


void RegisterLib(Core::Loader::SymbolsResolver* sym) {
    
    //LIB_FUNCTION("5yYjEdd4t8Y", "libSceNpSignaling", 1, "libSceNpSignaling", sceNpSignalingCreateContext);

    //LIB_FUNCTION("5yYjEdd4t8Y", "libSceNpSignaling", 1, "libSceNpSignaling", sceNpSignalingCreateContext);
    //LIB_FUNCTION("8533Q+LU7EQ", "libSceNpUtility", 1, "libSceNpUtility", sceNpLookupCreateTitleCtx);

    //LIB_FUNCTION("WkkeywLJcgU", "libc", 1, "libc", _wcstrlen);
    //LIB_FUNCTION("Q2V+iqvjgC0", "libc", 1, "libc", _vsnprintf);
    //LIB_FUNCTION("eLdDw6l0-bU", "libc", 1, "libc", _snprintf);
    //LIB_FUNCTION("tcVi5SivF7Q", "libc", 1, "libc", _sprintf);
    LIB_FUNCTION("Im55VJ-Bekc", "libc", 1, "libc", _swprintf);


    LIB_FUNCTION("AS45QoYHjc4", "libSceScreenShot", 1, "libSceScreenShot", _Z5dummyv);
    LIB_FUNCTION("JuMLLmmvRgk", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotCapture);
    LIB_FUNCTION("tIYf0W5VTi8", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotDisable);
    LIB_FUNCTION("ysfza71rm9M", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotDisableNotification);
    LIB_FUNCTION("2xxUtuC-RzE", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotEnable);
    LIB_FUNCTION("BDUaqlVdSAY", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotEnableNotification);
    LIB_FUNCTION("hNmK4SdhPT0", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotGetAppInfo);
    LIB_FUNCTION("VlAQIgXa2R0", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotGetDrcParam);
    LIB_FUNCTION("-SV-oTNGFQk", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotIsDisabled);
    LIB_FUNCTION("ICNJ-1POs84", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotIsVshScreenCaptureDisabled);
    LIB_FUNCTION("ahHhOf+QNkQ", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotSetOverlayImage);
    LIB_FUNCTION("73WQ4Jj0nJI", "libSceScreenShot", 1, "libSceScreenShot",
                 sceScreenShotSetOverlayImageWithOrigin);
    LIB_FUNCTION("G7KlmIYFIZc", "libSceScreenShot", 1, "libSceScreenShot", sceScreenShotSetParam);
    LIB_FUNCTION("itlWFWV3Tzc", "libSceScreenShotDrc", 1, "libSceScreenShot",
                 sceScreenShotSetDrcParam);
};

} // namespace Libraries::ScreenShot