#ifndef MININGINFOPAGE_H
#define MININGINFOPAGE_H

#include <QWidget>

//#include "walletmodel.h"

namespace Ui {
class MiningInfoPage;
}

class ClientModel;
class WalletModel;

class MiningInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit MiningInfoPage(QWidget *parent = 0);
    ~MiningInfoPage();

    void updatePlot();

private:

    Ui::MiningInfoPage *ui;

    ClientModel *clientModel;
    WalletModel *walletModel;

    QVector<double> vX;
    QVector<double> vY;

    QVector<double> vX2;
    QVector<double> vY2;

private slots:

};

#endif // MININGINFOPAGE_H
