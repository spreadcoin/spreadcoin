#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include <QWidget>

#include "bitcoingui.h"

namespace Ui {
    class OverviewPage;
}

class OverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewPage(QWidget *parent, BitcoinGUI *_gui);
    ~OverviewPage();

public slots:
    void gotoSendCoinsPage();
    void gotoVanityGenPage();
    void gotoMiningInfoPage();
    void gotoSettings();

signals:

private:
    Ui::OverviewPage *ui;
    BitcoinGUI *gui;

private slots:

};

#endif // OVERVIEWPAGE_H
