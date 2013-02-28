#include "../cpp/core/meewodshareui.hpp"

MeeWODShareUi::MeeWODShareUi() { }

MeeWODShareUi::~MeeWODShareUi() { }

void MeeWODShareUi::share(const QString &title, const QString &url)
{
    qDebug() << "Title " << title << " Url " << url;

#ifdef QT_SIMULATOR

    Q_UNUSED(title)
    Q_UNUSED(url)

#else

    // See https://meego.gitorious.org/meego-sharing-framework/share-ui/blobs/master/examples/link-share/page.cpp
    // and http://forum.meego.com/showthread.php?t=3768

    MDataUri dataUri;
    dataUri.setMimeType("text/x-url");
    dataUri.setTextData(url);
    dataUri.setAttribute("title", title);
    dataUri.setAttribute("description", tr("Shared with #MeeWOD for Harmattan"));

    QStringList items;

    items << dataUri.toString();

    ShareUiInterface shareIf("com.nokia.ShareUi");

    if (shareIf.isValid()) {
        shareIf.share(items);
    } else {
        qCritical() << "Invalid interface";
    }

#endif
}
