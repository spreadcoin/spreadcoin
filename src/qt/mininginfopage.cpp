#include "mininginfopage.h"
#include "ui_mininginfopage.h"

#include "clientmodel.h"
#include "walletmodel.h"

#include "main.h"
#include "bitcoinrpc.h"
#include "util.h"

extern json_spirit::Value GetNetworkHashPS(int lookup, int height);

MiningInfoPage::MiningInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiningInfoPage)
{
    ui->setupUi(this);

    // setup Plot
    // create graph
    ui->diffplot_difficulty->addGraph();

    // Use usual background
    ui->diffplot_difficulty->setBackground(QBrush(QColor(255,255,255,255)));//QWidget::palette().color(this->backgroundRole())));

    // give the axes some labels:
    ui->diffplot_difficulty->xAxis->setLabel(tr("Blocks"));
    ui->diffplot_difficulty->yAxis->setLabel(tr("Difficulty"));

    // set the pens
    //a13469
    ui->diffplot_difficulty->graph(0)->setPen(QPen(QColor(161, 52, 105), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));//QPen(QColor(76, 76, 229)));
    ui->diffplot_difficulty->graph(0)->setLineStyle(QCPGraph::lsLine);

    // set axes label fonts:
    QFont label = font();
    ui->diffplot_difficulty->xAxis->setLabelFont(label);
    ui->diffplot_difficulty->yAxis->setLabelFont(label);


    // setup Plot
    // create graph
    ui->diffplot_hashrate->addGraph();

    // Use usual background
    ui->diffplot_hashrate->setBackground(QBrush(QColor(255,255,255,255)));//QWidget::palette().color(this->backgroundRole())));

    // give the axes some labels:
    ui->diffplot_hashrate->xAxis->setLabel(tr("Blocks"));
    ui->diffplot_hashrate->yAxis->setLabel(tr("Hashrate MH/s"));

    // set the pens
    //a13469, 6c3d94
    ui->diffplot_hashrate->graph(0)->setPen(QPen(QColor(108, 61, 148), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));//QPen(QColor(76, 76, 229)));
    ui->diffplot_hashrate->graph(0)->setLineStyle(QCPGraph::lsLine);

    // set axes label fonts:
    QFont label2 = font();
    ui->diffplot_hashrate->xAxis->setLabelFont(label2);
    ui->diffplot_hashrate->yAxis->setLabelFont(label2);

}

MiningInfoPage::~MiningInfoPage()
{
    delete ui;
}

void MiningInfoPage::updatePlot()
{
    static int64_t lastUpdate = 0;

    // Double Check to make sure we don't try to update the plot when it is disabled
    if(!GetBoolArg("-chart", true)) { return; }
    if (GetTime() - lastUpdate < 60) { return; } // This is just so it doesn't redraw rapidly during syncing

    int numLookBack = 4320;
    double diffMax = 0;
    CBlockIndex* pindex = pindexBest;
    int height = nBestHeight;
    int xStart = std::max<int>(height-numLookBack, 0) + 1;
    int xEnd = height;

    // Start at the end and walk backwards
    int i = numLookBack-1;
    int x = xEnd;

    // This should be a noop if the size is already 2000
    vX.resize(numLookBack);
    vY.resize(numLookBack);

    CBlockIndex* itr = pindex;

    while(i >= 0 && itr != NULL)
    {
        vX[i] = itr->nHeight;
        vY[i] = GetDifficulty(itr);
        diffMax = std::max<double>(diffMax, vY[i]);

        itr = itr->pprev;
        i--;
        x--;
    }

    ui->diffplot_difficulty->graph(0)->setData(vX, vY);

    // set axes ranges, so we see all data:
    ui->diffplot_difficulty->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_difficulty->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_difficulty->xAxis->setAutoSubTicks(false);
    ui->diffplot_difficulty->yAxis->setAutoSubTicks(false);
    ui->diffplot_difficulty->xAxis->setSubTickCount(0);
    ui->diffplot_difficulty->yAxis->setSubTickCount(0);

    ui->diffplot_difficulty->replot();

    //

    diffMax = 0;

    // Start at the end and walk backwards
    i = numLookBack-1;
    x = xEnd;

    // This should be a noop if the size is already 2000
    vX2.resize(numLookBack);
    vY2.resize(numLookBack);

    CBlockIndex* itr2 = pindex;

    while(i >= 0 && itr2 != NULL)
    {
        vX2[i] = itr2->nHeight;
        vY2[i] =  (double)GetNetworkHashPS(120, itr2->nHeight).get_int64()/1000000;//GetDifficulty(itr);
        diffMax = std::max<double>(diffMax, vY2[i]);

        itr2 = itr2->pprev;
        i--;
        x--;
    }

    ui->diffplot_hashrate->graph(0)->setData(vX2, vY2);

    // set axes ranges, so we see all data:
    ui->diffplot_hashrate->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_hashrate->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_hashrate->xAxis->setAutoSubTicks(false);
    ui->diffplot_hashrate->yAxis->setAutoSubTicks(false);
    ui->diffplot_hashrate->xAxis->setSubTickCount(0);
    ui->diffplot_hashrate->yAxis->setSubTickCount(0);

    ui->diffplot_hashrate->replot();

    //


    lastUpdate = GetTime();
}
