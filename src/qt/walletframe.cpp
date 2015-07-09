/*
 * Qt4 bitcoin GUI.
 *
 * W.J. van der Laan 2011-2012
 * The Bitcoin Developers 2011-2013
 */
#include "walletframe.h"
#include "bitcoingui.h"
#include "walletstack.h"
#include "walletview.h"
#include "guiheader.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>

#include <QDebug>


WalletFrame::WalletFrame(BitcoinGUI *_gui) :
    QFrame(_gui),
    gui(_gui),
    clientModel(0)
{
    walletStack = new WalletStack(this);
    walletStack->setBitcoinGUI(gui);
    walletStack->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );

    QLabel *noWallet = new QLabel(tr("No wallet has been loaded."));
    noWallet->setAlignment(Qt::AlignCenter);
    walletStack->addWidget(noWallet);

    resizeIt();
}

WalletFrame::~WalletFrame()
{
}

void WalletFrame::resizeIt()
{
    if(screenId == 0){
        walletStack->setGeometry(100,120+5,this->width()-105, this->height()-10-120);
    } else{
        walletStack->setGeometry(100,120+40+5,this->width()-105, this->height()-10-120-40);
    }
}

void WalletFrame::resizeWhenFinished(){
    resizeIt();
}

void WalletFrame::stretchStack(int x, int y, int width, int height)
{
    QPropertyAnimation *animation = new QPropertyAnimation(walletStack, "geometry");
        animation->setDuration(100);
        animation->setStartValue(QRect(walletStack->x(),walletStack->y(),walletStack->width(), walletStack->height()));
        animation->setEndValue(QRect(x, y, width, height));
        animation->setEasingCurve(QEasingCurve::InCubic);
        animation->start();

        connect(animation, SIGNAL(finished()), this, SLOT(resizeWhenFinished()));
}

void WalletFrame::setClientModel(ClientModel *clientModel)
{
    this->clientModel = clientModel;
    walletStack->setClientModel(clientModel);
}

bool WalletFrame::addWallet(const QString& name, WalletModel *walletModel)
{
    return walletStack->addWallet(name, walletModel);
}

bool WalletFrame::setCurrentWallet(const QString& name)
{
    // TODO: Check if valid name
    walletStack->setCurrentWallet(name);
    return true;
}

void WalletFrame::removeAllWallets()
{
    walletStack->removeAllWallets();
}

bool WalletFrame::handleURI(const QString &uri)
{
    WalletView *walletView = currentWalletView();
    if (!walletView)
        return false;

    return walletStack->handleURI(uri);
}

void WalletFrame::showOutOfSyncWarning(bool fShow)
{
    if (!walletStack) {
        QMessageBox box;
        box.setText("walletStack is null");
        box.exec();
        return;
    }
    walletStack->showOutOfSyncWarning(fShow);
}

void WalletFrame::gotoOverviewPage()
{
    walletStack->gotoOverviewPage();
}

void WalletFrame::gotoHistoryPage()
{
    walletStack->gotoHistoryPage();
}

void WalletFrame::gotoVanityGenPage()
{
    walletStack->gotoVanityGenPage();
}

void WalletFrame::gotoAddressBookPage()
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletStack->gotoAddressBookPage();
}

void WalletFrame::gotoReceiveCoinsPage()
{
    walletStack->gotoReceiveCoinsPage();
}

void WalletFrame::gotoSendCoinsPage(QString addr)
{
    walletStack->gotoSendCoinsPage(addr);
}

void WalletFrame::gotoMiningPage()
{
    walletStack->gotoMiningPage();
}

void WalletFrame::gotoMiningInfoPage()
{
    walletStack->gotoMiningInfoPage();
}

void WalletFrame::gotoSignMessageTab(QString addr)
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->gotoSignMessageTab(addr);
}

void WalletFrame::gotoVerifyMessageTab(QString addr)
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->gotoVerifyMessageTab(addr);
}

void WalletFrame::encryptWallet(bool status)
{
    qDebug() << "status" << status;
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->encryptWallet(status);
}

void WalletFrame::backupWallet()
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->backupWallet();
}

void WalletFrame::changePassphrase()
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->changePassphrase();
}

void WalletFrame::unlockWallet()
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletView->unlockWallet();
}

void WalletFrame::setEncryptionStatus()
{
    WalletView *walletView = currentWalletView();
    if (walletView)
        walletStack->setEncryptionStatus();
}

WalletView *WalletFrame::currentWalletView()
{
    return qobject_cast<WalletView*>(walletStack->currentWidget());
}

void WalletFrame::updatePlot()
{
    walletStack->updatePlot();
}

