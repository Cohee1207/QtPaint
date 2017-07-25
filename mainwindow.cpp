#include <QColorDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageWriter>
#include <QCheckBox>
#include <QMessageBox>
#include <QDockWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newimagedialog.h"
#include "paintarea.h"
#include "zoomslider.h"

static const QString FORMATS_FILTER = QStringLiteral("Images (*.png *.bmp *.jpg *.jpeg *.gif);;All files (*.*)");
static const QString PICTURES_PATH = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
static const QString DEFAULT_FILE_NAME = QStringLiteral("Unnamed");
static const int MESSAGE_TIMEOUT = 5000; // 5 sec


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_paintArea = ui->openGLWidget;
    m_fileName = DEFAULT_FILE_NAME;
    m_layersList = new LayersList;
    setStatusBar();
    setToolBox();
    setDock();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_file_triggered()
{
    auto file = QFileDialog::getOpenFileName(this, QStringLiteral("Open image"), PICTURES_PATH, FORMATS_FILTER);
    if (file.isNull()) {
        return;
    }
    if (m_paintArea->loadImage(file)) {
        ui->statusBar->showMessage(QStringLiteral("Opened ") + file, MESSAGE_TIMEOUT);
        m_filePath = file;
        m_fileName = QFileInfo(file).fileName();
    }
    else {
        ui->statusBar->showMessage(QStringLiteral("Can't open ") + file, MESSAGE_TIMEOUT);
    }
}

void MainWindow::on_actionSave_file_triggered()
{
    static const QString SAVE_SUCCESS = QStringLiteral("Saved image to ");
    static const QString SAVE_FAILED = QStringLiteral("Can't save to ");
    bool result = QFileInfo(m_filePath).exists() ? saveExistingFile() : saveNewFile();
    ui->statusBar->showMessage((result ? SAVE_SUCCESS : SAVE_FAILED) + m_fileName, MESSAGE_TIMEOUT);
}

void MainWindow::on_actionSelect_color_triggered()
{
    m_strokeColorLabel.openColorSelectionDialog();
}

void MainWindow::on_actionIncrease_pen_width_triggered()
{
    m_widthButton->setWidthText(m_paintArea->increasePenWidth());
}

void MainWindow::on_actionDecrease_pen_width_triggered()
{
    m_widthButton->setWidthText(m_paintArea->decreasePenWidth());
}

void MainWindow::on_actionShow_drawn_toggled(bool)
{

}

void MainWindow::setToolBox()
{
    auto tools = m_paintArea->tools();
    for (int i = 0; i < tools->size(); i++) {
        auto tool = tools->at(i);
        QIcon icon;
        icon.addFile(":/icons/" + tool->iconName() + ".png");
        m_toolbox.addItem(icon, tool->toolName());
    }
    connect(&m_toolbox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), m_paintArea, &PaintArea::setSelectedTool);
}

void MainWindow::setStatusBar()
{
    m_widthButton = new WidthButton(this);
    auto checkButton = new QCheckBox(QStringLiteral("Antialiasing"));
    checkButton->setChecked(m_paintArea->antialiasingEnabled());
    connect(checkButton, &QCheckBox::toggled, m_paintArea, &PaintArea::setAntialiasingEnabled);
    ui->statusBar->addPermanentWidget(m_widthButton);
    ui->statusBar->addPermanentWidget(new QLabel(QStringLiteral("Stroke color:")));
    ui->statusBar->addPermanentWidget(&m_strokeColorLabel);
    ui->statusBar->addPermanentWidget(new QLabel(QStringLiteral("Fill color:")));
    ui->statusBar->addPermanentWidget(&m_fillColorLabel);
    ui->statusBar->addPermanentWidget(new QLabel(QStringLiteral("Tool:")));
    ui->statusBar->addPermanentWidget(&m_toolbox);
    ui->statusBar->addPermanentWidget(checkButton);
    connect(m_widthButton->widthSlider(), &QSlider::valueChanged, m_paintArea, &PaintArea::setPenWidth);
    m_strokeColorLabel.setColor(m_paintArea->pen().color());
    connect(m_strokeColorLabel.dialog(), &QColorDialog::colorSelected, m_paintArea, &PaintArea::setPenColor);
    m_fillColorLabel.setColor(m_paintArea->brush().color());
    connect(m_fillColorLabel.dialog(), &QColorDialog::colorSelected, m_paintArea, &PaintArea::setBrushColor);
    auto zoom = new ZoomSlider();
    connect(zoom->slider(), &QSlider::valueChanged, m_paintArea, &PaintArea::setZoom);
    ui->statusBar->addPermanentWidget(zoom);
}

void MainWindow::setDock()
{
    static QLabel* title = new QLabel(QStringLiteral("Layers"));
    title->setAlignment(Qt::AlignHCenter);
    m_dock.setTitleBarWidget(title);
    m_dock.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dock.setWidget(m_layersList);
    addDockWidget(Qt::RightDockWidgetArea, &m_dock);
}

bool MainWindow::saveExistingFile()
{
    return (m_paintArea->saveImage().save(m_filePath));
}

bool MainWindow::saveNewFile()
{
    QString filter = QStringLiteral("All files (*.*);;");
    foreach (const auto& x, QImageWriter::supportedImageFormats()) {
        filter += QStringLiteral(".") += QString::fromLatin1(x) += QStringLiteral(";;");
    }
    filter.chop(2);
    m_filePath = QFileDialog::getSaveFileName(this, QStringLiteral("Save image"), PICTURES_PATH, filter);
    if (m_filePath.isNull()) {
        return false;
    }
    m_fileName = QFileInfo(m_filePath).fileName();
    return m_paintArea->saveImage().save(m_filePath);
}

int MainWindow::confirmSaveAction()
{
    return QMessageBox::question(this, QStringLiteral(""), QStringLiteral("Save changes to ") + m_fileName + QStringLiteral("?"), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
}

void MainWindow::on_actionNew_image_triggered()
{
    switch (confirmSaveAction()) {
    case QMessageBox::Yes:
        on_actionSave_file_triggered();
        break;
    case QMessageBox::Cancel:
        return;
    }
    auto dlg = new NewImageDialog(this);
    dlg->setWindowModality(Qt::WindowModal);
    if (dlg->exec()) {
        m_paintArea->setDefaultLayer(dlg->width(), dlg->height(), dlg->color());
        m_fileName = DEFAULT_FILE_NAME;
        m_filePath = DEFAULT_FILE_NAME;
    }
}

void MainWindow::on_actionPaste_triggered()
{
    switch (confirmSaveAction()) {
    case QMessageBox::Yes:
        on_actionSave_file_triggered();
        break;
    case QMessageBox::Cancel:
        return;
    }
    if (!m_paintArea->pasteImage()) {
        ui->statusBar->showMessage(QStringLiteral("Clipboard doesn't contain acceptable image"), MESSAGE_TIMEOUT);
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox(this);
    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/app.png"));
    msgBox.setWindowTitle(QStringLiteral("About"));
    msgBox.setIconPixmap(icon.pixmap(QSize(64, 64)));
    msgBox.setTextFormat(Qt::RichText);   //this is what makes the links clickable
    msgBox.setText(QStringLiteral("Contains icons from Oxygen theme by KDE licensed with LGPL: <a href='https://github.com/KDE/oxygen-icons5'>GitHub</a>"));
    msgBox.exec();
}

void MainWindow::on_actionClear_drawn_triggered()
{
    if (QMessageBox::question(this, QStringLiteral(""), QStringLiteral("Are you sure? All changes will be lost.")) == QMessageBox::Yes) {
        m_paintArea->setDefaultLayer();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    m_paintArea->copyImage();
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    switch (confirmSaveAction()) {
    case QMessageBox::Yes:
        on_actionSave_file_triggered();
        break;
    case QMessageBox::Cancel:
        e->setAccepted(false);
        return;
    }
}

PaintArea* MainWindow::paintArea() const
{
    return m_paintArea;
}

void MainWindow::on_actionFlip_horizontal_triggered()
{
    m_paintArea->transform(PaintArea::FLIP_HORIZONTAL);
}

void MainWindow::on_actionFlip_vertical_triggered()
{
    m_paintArea->transform(PaintArea::FLIP_VERTICAL);
}

void MainWindow::on_actionRotate_left_triggered()
{
    m_paintArea->transform(PaintArea::ROTATE_LEFT);
}

void MainWindow::on_actionRotate_right_triggered()
{
    m_paintArea->transform(PaintArea::ROTATE_RIGHT);
}

void MainWindow::on_actionLayers_triggered(bool checked)
{
    m_dock.setVisible(checked);
}
