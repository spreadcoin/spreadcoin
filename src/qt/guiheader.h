#ifndef GUIHEADER_H
#define GUIHEADER_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>
#include <QSignalMapper>
#include <QSystemTrayIcon>

class ClientModel;
class WalletModel;
class TransactionFilterProxy;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class ClickableLabel;

extern int screenId;



class ClickableLabel : public QLabel
{

    Q_OBJECT

public:
    explicit ClickableLabel(QWidget * parent = 0 );
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;
};


class GuiHeader : public QWidget
{
    Q_OBJECT

public:

    explicit GuiHeader(QWidget *parent = 0);
    ~GuiHeader();

    void setClientModel(ClientModel *clientModel);
    void setWalletModel(WalletModel *walletModel);

    QWidget *backGround;
    QWidget *bottomLine;

    QFrame *walletOverview;
    QLabel *walletTitle;

    QFrame *recentOverview;

    QFrame *networkOverview;
    QLabel *networkTitle;

    QWidget *recentOverviewCol[3];
    QVBoxLayout *recentColLayout[3];
    ClickableLabel *recentLabel[3][3];

    QTimer *timer;

    void resize(int);
    void showOutOfSyncWarning(bool fShow);

    void updateNetworkOverview();

    TransactionFilterProxy *filter;
    QSignalMapper *mapper[3][3];

public slots:
    void setBalance(qint64 balance, qint64 unconfirmedBalance, qint64 immatureBalance);
    void handleTransactionClicked(int indexa);
signals:
    void transactionClicked2(const QModelIndex &index);
    void transactionClicked(int index);

private:
    ClickableLabel *spreadCoinLogo;

    ClientModel *clientModel;
    WalletModel *walletModel;
    qint64 currentBalance;
    qint64 currentUnconfirmedBalance;
    qint64 currentImmatureBalance;

    QLabel *versionLabel;

    QLabel *labelBalance;
    QLabel *labelUnconfirmedBalance;
    QLabel *labelImmatureBalance;

    QLabel *blockCount;
    QLabel *moneySupply;
    QLabel *hashRate;

    int unit;

private slots:
    void updateDisplayUnit();

};

#endif // GUIHEADER_H
