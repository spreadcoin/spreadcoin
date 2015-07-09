#include "overviewpage.h"
#include "ui_overviewpage.h"

#include "bitcoingui.h"

#include "guiheader.h"

#include <QDebug>

OverviewPage::OverviewPage(QWidget *parent, BitcoinGUI *_gui):
    QWidget(parent),
    gui(_gui),
    ui(new Ui::OverviewPage)
{
    ui->setupUi(this);

    //#a13469 #6c3d94

    ui->labelIntroText->setStyleSheet(".QLabel{color:#000000; border: 1px solid black;background-color: #C3C0BB; padding:10px;}");
    ui->labelIntroText->setText("<b>Welcome to SpreadCoin, "
                                "the project that is building a network where any possible application "
                                "or service can be run in a decentralised manner.</b>");
#ifdef Q_OS_WIN32
    ui->labelIntroText->setFixedHeight(50);
#else
    ui->labelIntroText->setFixedHeight(60);
#endif

    ClickableLabel *JumpSelector = new ClickableLabel();//Label(this);
    ClickableLabel *JumpSelector2 = new ClickableLabel();
    ClickableLabel *JumpSelector3 = new ClickableLabel();
    ClickableLabel *JumpSelector4 = new ClickableLabel();

    JumpSelector->setStyleSheet(".ClickableLabel{background-color: #EEEEEE; border: none; border-radius: 10px; padding:10px;}");
    JumpSelector2->setStyleSheet(".ClickableLabel{background-color: #EEEEEE; border: none; border-radius: 10px; padding:10px;}");
    JumpSelector3->setStyleSheet(".ClickableLabel{background-color: #EEEEEE; border: none; border-radius: 10px; padding:10px;}");
    JumpSelector4->setStyleSheet(".ClickableLabel{background-color: #EEEEEE; border: none; border-radius: 10px; padding:10px;}");

    JumpSelector->setWordWrap(true);
    JumpSelector2->setWordWrap(true);
    JumpSelector3->setWordWrap(true);
    JumpSelector4->setWordWrap(true);

    JumpSelector->setCursor(QCursor(Qt::PointingHandCursor));
    JumpSelector2->setCursor(QCursor(Qt::PointingHandCursor));
    JumpSelector3->setCursor(QCursor(Qt::PointingHandCursor));
    JumpSelector4->setCursor(QCursor(Qt::PointingHandCursor));

    JumpSelector->setText("<span style='font-size:12pt;'><b>Wallet</b></span><br><br>"
                   "<span style='font-size:10pt;'>Send and receive coins, view your transactions, manage your address book and backup your wallet.</span>");
    JumpSelector2->setText("<span style='font-size:12pt;'><b>Vanity Gen</b></span><br><br>"
                    "<span style='font-size:10pt;'>Create uniquely recognizable<br>SPR addresses with the in-wallet Vanity Address Generator.</span>");
    JumpSelector3->setText("<span style='font-size:12pt;'><b>Mining</b></span><br><br>"
                    "<span style='font-size:10pt;'>View<br>current and historical<br>network mining data.</span>");
    JumpSelector4->setText("<span style='font-size:12pt;'><b>Settings</b></span><br><br>"
                    "<span style='font-size:10pt;'>Change local network settings, application behaviour and <br>display options.</span>");

    JumpSelector->setAlignment(Qt::AlignCenter);
    JumpSelector2->setAlignment(Qt::AlignCenter);
    JumpSelector3->setAlignment(Qt::AlignCenter);
    JumpSelector4->setAlignment(Qt::AlignCenter);

    JumpSelector->setFixedWidth(200);
    JumpSelector->setMinimumHeight(100);
    JumpSelector2->setFixedWidth(200);
    JumpSelector2->setMinimumHeight(100);
    JumpSelector3->setFixedWidth(200);
    JumpSelector3->setMinimumHeight(100);
    JumpSelector4->setFixedWidth(200);
    JumpSelector4->setMinimumHeight(100);

    ui->gridLayout->addWidget(JumpSelector,0,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(JumpSelector2,0,1,Qt::AlignCenter);
    ui->gridLayout->addWidget(JumpSelector3,1,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(JumpSelector4,1,1,Qt::AlignCenter);

    connect(JumpSelector, SIGNAL(clicked()), this,SLOT(gotoSendCoinsPage()));
    connect(JumpSelector2, SIGNAL(clicked()), this,SLOT(gotoVanityGenPage()));
    connect(JumpSelector3, SIGNAL(clicked()), this,SLOT(gotoMiningInfoPage()));
    connect(JumpSelector4, SIGNAL(clicked()), this,SLOT(gotoSettings()));


    ui->linkLabel1->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #6c3d94; border: none; border-radius: 10px; padding:10px;}");
    ui->linkLabel2->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #6c3d94; border: none; border-radius: 10px; padding:10px;}");
    ui->linkLabel3->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #6c3d94; border: none; border-radius: 10px; padding:10px;}");

    ui->linkLabel1->setOpenExternalLinks(true);
    ui->linkLabel2->setOpenExternalLinks(true);
    ui->linkLabel3->setOpenExternalLinks(true);

    ui->linkLabel1->setTextFormat(Qt::RichText);

    ui->linkLabel1->setText("<a style='text-decoration:none; ' href='http://www.spreadcoin.info'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Official Website</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>For the most up-to-date Downloads or News</span>"
                            "</a>");
    ui->linkLabel2->setText("<a style='text-decoration:none; ' href='http://www.spreadcointalk.org'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Official Forum</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>For Tutorials and Technical Support</span>"
                            "</a>");
    ui->linkLabel3->setText("<a style='text-decoration:none; ' href='https://bitcointalk.org/index.php?topic=1045373.0'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Bitcointalk Forum</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>For General Discussion</span>"
                            "</a>");
}

OverviewPage::~OverviewPage()
{
    delete ui;
}

void OverviewPage::gotoSendCoinsPage()
{

    gui->gotoSendCoinsPage();
}

void OverviewPage::gotoVanityGenPage()
{
    gui->gotoVanityGenPage();
}

void OverviewPage::gotoMiningInfoPage()
{
    gui->gotoMiningInfoPage();
}

void OverviewPage::gotoSettings()
{
    gui->optionsClicked();
}
