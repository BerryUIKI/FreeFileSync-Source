// *****************************************************************************
// * This file is part of the FreeFileSync project. It is distributed under    *
// * GNU General Public License: https://www.gnu.org/licenses/gpl-3.0          *
// * Copyright (C) Zenju (zenju AT freefilesync DOT org) - All Rights Reserved *
// *****************************************************************************

#include "sys_error.h"
    #include <gio/gio.h>

using namespace zen;


namespace
{
std::wstring formatSystemErrorCode(ErrorCode ec)
{
    switch (ec) //pretty much all codes currently used on CentOS 7 and macOS 10.15
    {
            ZEN_CASE_RETURN_STRING(EPERM);
            ZEN_CASE_RETURN_STRING(ENOENT);
            ZEN_CASE_RETURN_STRING(ESRCH);
            ZEN_CASE_RETURN_STRING(EINTR);
            ZEN_CASE_RETURN_STRING(EIO);
            ZEN_CASE_RETURN_STRING(ENXIO);
            ZEN_CASE_RETURN_STRING(E2BIG);
            ZEN_CASE_RETURN_STRING(ENOEXEC);
            ZEN_CASE_RETURN_STRING(EBADF);
            ZEN_CASE_RETURN_STRING(ECHILD);
            ZEN_CASE_RETURN_STRING(EAGAIN);
            ZEN_CASE_RETURN_STRING(ENOMEM);
            ZEN_CASE_RETURN_STRING(EACCES);
            ZEN_CASE_RETURN_STRING(EFAULT);
            ZEN_CASE_RETURN_STRING(ENOTBLK);
            ZEN_CASE_RETURN_STRING(EBUSY);
            ZEN_CASE_RETURN_STRING(EEXIST);
            ZEN_CASE_RETURN_STRING(EXDEV);
            ZEN_CASE_RETURN_STRING(ENODEV);
            ZEN_CASE_RETURN_STRING(ENOTDIR);
            ZEN_CASE_RETURN_STRING(EISDIR);
            ZEN_CASE_RETURN_STRING(EINVAL);
            ZEN_CASE_RETURN_STRING(ENFILE);
            ZEN_CASE_RETURN_STRING(EMFILE);
            ZEN_CASE_RETURN_STRING(ENOTTY);
            ZEN_CASE_RETURN_STRING(ETXTBSY);
            ZEN_CASE_RETURN_STRING(EFBIG);
            ZEN_CASE_RETURN_STRING(ENOSPC);
            ZEN_CASE_RETURN_STRING(ESPIPE);
            ZEN_CASE_RETURN_STRING(EROFS);
            ZEN_CASE_RETURN_STRING(EMLINK);
            ZEN_CASE_RETURN_STRING(EPIPE);
            ZEN_CASE_RETURN_STRING(EDOM);
            ZEN_CASE_RETURN_STRING(ERANGE);
            ZEN_CASE_RETURN_STRING(EDEADLK);
            ZEN_CASE_RETURN_STRING(ENAMETOOLONG);
            ZEN_CASE_RETURN_STRING(ENOLCK);
            ZEN_CASE_RETURN_STRING(ENOSYS);
            ZEN_CASE_RETURN_STRING(ENOTEMPTY);
            ZEN_CASE_RETURN_STRING(ELOOP);
            ZEN_CASE_RETURN_STRING(ENOMSG);
            ZEN_CASE_RETURN_STRING(EIDRM);
            ZEN_CASE_RETURN_STRING(ENOSTR);
            ZEN_CASE_RETURN_STRING(ENODATA);
            ZEN_CASE_RETURN_STRING(ETIME);
            ZEN_CASE_RETURN_STRING(ENOSR);
            ZEN_CASE_RETURN_STRING(EREMOTE);
            ZEN_CASE_RETURN_STRING(ENOLINK);
            ZEN_CASE_RETURN_STRING(EPROTO);
            ZEN_CASE_RETURN_STRING(EMULTIHOP);
            ZEN_CASE_RETURN_STRING(EBADMSG);
            ZEN_CASE_RETURN_STRING(EOVERFLOW);
            ZEN_CASE_RETURN_STRING(EILSEQ);
            ZEN_CASE_RETURN_STRING(EUSERS);
            ZEN_CASE_RETURN_STRING(ENOTSOCK);
            ZEN_CASE_RETURN_STRING(EDESTADDRREQ);
            ZEN_CASE_RETURN_STRING(EMSGSIZE);
            ZEN_CASE_RETURN_STRING(EPROTOTYPE);
            ZEN_CASE_RETURN_STRING(ENOPROTOOPT);
            ZEN_CASE_RETURN_STRING(EPROTONOSUPPORT);
            ZEN_CASE_RETURN_STRING(ESOCKTNOSUPPORT);
            ZEN_CASE_RETURN_STRING(ENOTSUP);
            ZEN_CASE_RETURN_STRING(EPFNOSUPPORT);
            ZEN_CASE_RETURN_STRING(EAFNOSUPPORT);
            ZEN_CASE_RETURN_STRING(EADDRINUSE);
            ZEN_CASE_RETURN_STRING(EADDRNOTAVAIL);
            ZEN_CASE_RETURN_STRING(ENETDOWN);
            ZEN_CASE_RETURN_STRING(ENETUNREACH);
            ZEN_CASE_RETURN_STRING(ENETRESET);
            ZEN_CASE_RETURN_STRING(ECONNABORTED);
            ZEN_CASE_RETURN_STRING(ECONNRESET);
            ZEN_CASE_RETURN_STRING(ENOBUFS);
            ZEN_CASE_RETURN_STRING(EISCONN);
            ZEN_CASE_RETURN_STRING(ENOTCONN);
            ZEN_CASE_RETURN_STRING(ESHUTDOWN);
            ZEN_CASE_RETURN_STRING(ETOOMANYREFS);
            ZEN_CASE_RETURN_STRING(ETIMEDOUT);
            ZEN_CASE_RETURN_STRING(ECONNREFUSED);
            ZEN_CASE_RETURN_STRING(EHOSTDOWN);
            ZEN_CASE_RETURN_STRING(EHOSTUNREACH);
            ZEN_CASE_RETURN_STRING(EALREADY);
            ZEN_CASE_RETURN_STRING(EINPROGRESS);
            ZEN_CASE_RETURN_STRING(ESTALE);
            ZEN_CASE_RETURN_STRING(EDQUOT);
            ZEN_CASE_RETURN_STRING(ECANCELED);
            ZEN_CASE_RETURN_STRING(EOWNERDEAD);
            ZEN_CASE_RETURN_STRING(ENOTRECOVERABLE);

            ZEN_CASE_RETURN_STRING(ECHRNG);
            ZEN_CASE_RETURN_STRING(EL2NSYNC);
            ZEN_CASE_RETURN_STRING(EL3HLT);
            ZEN_CASE_RETURN_STRING(EL3RST);
            ZEN_CASE_RETURN_STRING(ELNRNG);
            ZEN_CASE_RETURN_STRING(EUNATCH);
            ZEN_CASE_RETURN_STRING(ENOCSI);
            ZEN_CASE_RETURN_STRING(EL2HLT);
            ZEN_CASE_RETURN_STRING(EBADE);
            ZEN_CASE_RETURN_STRING(EBADR);
            ZEN_CASE_RETURN_STRING(EXFULL);
            ZEN_CASE_RETURN_STRING(ENOANO);
            ZEN_CASE_RETURN_STRING(EBADRQC);
            ZEN_CASE_RETURN_STRING(EBADSLT);
            ZEN_CASE_RETURN_STRING(EBFONT);
            ZEN_CASE_RETURN_STRING(ENONET);
            ZEN_CASE_RETURN_STRING(ENOPKG);
            ZEN_CASE_RETURN_STRING(EADV);
            ZEN_CASE_RETURN_STRING(ESRMNT);
            ZEN_CASE_RETURN_STRING(ECOMM);
            ZEN_CASE_RETURN_STRING(EDOTDOT);
            ZEN_CASE_RETURN_STRING(ENOTUNIQ);
            ZEN_CASE_RETURN_STRING(EBADFD);
            ZEN_CASE_RETURN_STRING(EREMCHG);
            ZEN_CASE_RETURN_STRING(ELIBACC);
            ZEN_CASE_RETURN_STRING(ELIBBAD);
            ZEN_CASE_RETURN_STRING(ELIBSCN);
            ZEN_CASE_RETURN_STRING(ELIBMAX);
            ZEN_CASE_RETURN_STRING(ELIBEXEC);
            ZEN_CASE_RETURN_STRING(ERESTART);
            ZEN_CASE_RETURN_STRING(ESTRPIPE);
            ZEN_CASE_RETURN_STRING(EUCLEAN);
            ZEN_CASE_RETURN_STRING(ENOTNAM);
            ZEN_CASE_RETURN_STRING(ENAVAIL);
            ZEN_CASE_RETURN_STRING(EISNAM);
            ZEN_CASE_RETURN_STRING(EREMOTEIO);
            ZEN_CASE_RETURN_STRING(ENOMEDIUM);
            ZEN_CASE_RETURN_STRING(EMEDIUMTYPE);
            ZEN_CASE_RETURN_STRING(ENOKEY);
            ZEN_CASE_RETURN_STRING(EKEYEXPIRED);
            ZEN_CASE_RETURN_STRING(EKEYREVOKED);
            ZEN_CASE_RETURN_STRING(EKEYREJECTED);
            ZEN_CASE_RETURN_STRING(ERFKILL);
            ZEN_CASE_RETURN_STRING(EHWPOISON);
        default:
            return replaceCpy(_("Error code %x"), L"%x", numberTo<std::wstring>(ec));
    }
}
}


std::wstring zen::formatGlibError(const std::string& functionName, GError* error)
{
    if (!error)
        return formatSystemError(functionName, L"", _("Error description not available.") + L" null GError");

    if (error->domain == G_FILE_ERROR) //"values corresponding to errno codes"
        return formatSystemError(functionName, error->code);

    std::wstring errorCode;
    if (error->domain == G_IO_ERROR)
        errorCode = [&] -> std::wstring
    {
        switch (error->code) //GIOErrorEnum: https://gitlab.gnome.org/GNOME/glib/-/blob/master/gio/gioenums.h#L530
        {
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_FAILED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_FOUND);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_EXISTS);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_IS_DIRECTORY);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_DIRECTORY);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_EMPTY);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_REGULAR_FILE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_SYMBOLIC_LINK);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_MOUNTABLE_FILE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_FILENAME_TOO_LONG);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_INVALID_FILENAME);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_TOO_MANY_LINKS);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NO_SPACE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_INVALID_ARGUMENT);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PERMISSION_DENIED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_SUPPORTED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_MOUNTED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_ALREADY_MOUNTED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_CLOSED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_CANCELLED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PENDING);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_READ_ONLY);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_CANT_CREATE_BACKUP);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_WRONG_ETAG);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_TIMED_OUT);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_WOULD_RECURSE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_BUSY);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_WOULD_BLOCK);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_HOST_NOT_FOUND);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_WOULD_MERGE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_FAILED_HANDLED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_TOO_MANY_OPEN_FILES);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_INITIALIZED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_ADDRESS_IN_USE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PARTIAL_INPUT);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_INVALID_DATA);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_DBUS_ERROR);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_HOST_UNREACHABLE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NETWORK_UNREACHABLE);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_CONNECTION_REFUSED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PROXY_FAILED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PROXY_AUTH_FAILED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PROXY_NEED_AUTH);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_PROXY_NOT_ALLOWED);
#ifndef GLIB_CHECK_VERSION //e.g Debian 8 (GLib 2.42)     CentOS 7 (GLib 2.56)
#error Where is GLib?
#endif
#if GLIB_CHECK_VERSION(2, 44, 0)
                static_assert(G_IO_ERROR_BROKEN_PIPE == G_IO_ERROR_CONNECTION_CLOSED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_CONNECTION_CLOSED);
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_NOT_CONNECTED);
#endif
#if GLIB_CHECK_VERSION(2, 48, 0)
                ZEN_CASE_RETURN_STRING(G_IO_ERROR_MESSAGE_TOO_LARGE);
#endif
            default:
                return replaceCpy<std::wstring>(L"GIO error %x", L"%x", numberTo<std::wstring>(error->code));
        }
    }();
    else
    {
        //g-file-error-quark => g-file-error
        //g-io-error-quark   => g-io-error
        std::wstring domain = utfTo<std::wstring>(::g_quark_to_string(error->domain)); //e.g. "g-io-error-quark"
        if (endsWith(domain, L"-quark"))
            domain = beforeLast(domain, L"-", IfNotFoundReturn::none);

        errorCode = domain + L' ' + numberTo<std::wstring>(error->code); //e.g. "g-io-error 15"
    }

    const std::wstring errorMsg = utfTo<std::wstring>(error->message); //e.g. "Unable to find or create trash directory for file.txt"

    return formatSystemError(functionName, errorCode, errorMsg);
}



std::wstring zen::getSystemErrorDescription(ErrorCode ec) //return empty string on error
{
    const ErrorCode ecCurrent = getLastError(); //not necessarily == ec
    ZEN_ON_SCOPE_EXIT(errno = ecCurrent);

    std::wstring errorMsg = utfTo<std::wstring>(::g_strerror(ec)); //... vs strerror(): "marginally improves thread safety, and marginally improves consistency"

    trim(errorMsg); //Windows messages seem to end with a space...
    return errorMsg;
}


std::wstring zen::formatSystemError(const std::string& functionName, ErrorCode ec)
{
    return formatSystemError(functionName, formatSystemErrorCode(ec), getSystemErrorDescription(ec));
}


std::wstring zen::formatSystemError(const std::string& functionName, const std::wstring& errorCode, const std::wstring& errorMsg)
{
    std::wstring output = trimCpy(errorCode);

    const std::wstring errorMsgFmt = trimCpy(errorMsg);
    if (!output.empty() && !errorMsgFmt.empty())
        output += L": ";

    output += errorMsgFmt;

    if (!functionName.empty())
        output += L" [" + utfTo<std::wstring>(functionName) + L']';

    return trimCpy(output);
}
