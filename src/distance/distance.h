
#ifndef DISTANCE_H
#define DISTANCE_H
// #ifdef __aarch64__
#include <QtGlobal>
#include <QWidget>
#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
#include <QLabel>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QVideoFrame>
#include <QAbstractVideoBuffer>
#include <QImage>
#include <QTimer>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QEvent>
#include <QLineEdit>
#include <QStringList>
#include <QMutex>
#include <QDir>
#include <QHash>
#include <QSize>
#include <QVector>

#include "usage.h"
#include "yolo11.h" // for rknn_app_context_t
#include "image_utils.h"
#include "file_utils.h"
#include "image_drawing.h"
#include <opencv2/opencv.hpp>

namespace Ui
{
    class distance;
}

class distance; // 前向声明

// 独立的虚拟键盘事件过滤器类
class VirtualKeyboardFilter : public QObject
{
    Q_OBJECT
public:
    explicit VirtualKeyboardFilter(distance *parent);
    distance *parentDistance;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

class distance : public QWidget
{
    Q_OBJECT
    friend class VirtualKeyboardFilter;

public:
    explicit distance(QWidget *parent = nullptr);
    ~distance();

    struct FocalParams
    {
        double f = 0.0;
        double fy = 0.0;
    };

private slots:
    void on_back_btn_clicked();
    void on_back_btn_2_clicked();
    void on_back_btn_3_clicked();
    void on_flip_btn_clicked();

    void processFrame(const QVideoFrame &frame); // 新增槽
    void on_comboBox_currentIndexChanged(int index);
    void on_lineEdit_1_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_usage_btn_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_6_currentIndexChanged(int index);

    void on_comboBox_7_currentIndexChanged(int index);

    void on_scrshotBtn_clicked();
    void on_zBtn_clicked();
    void on_xBtn_clicked();
    void on_show1Btn_clicked();
    void on_filterBtn_clicked();

public slots:
    void showVirtualKeyboard();
    void onVirtualKeyboardButtonClicked(const QString &text);
    void onVirtualKeyboardBackspace();
    void onVirtualKeyboardClear();
    void onVirtualKeyboardOK();
    void handleLogMessage(const QString &line);

private:
    void syncPriorSizeToLineEdit();
    bool updatePriorSizeFromLineEdit();
    void syncCameraHeightToLineEdit();
    bool updateCameraHeightFromLineEdit();
    void setActiveLineEdit(QLineEdit *edit);
    bool applyFrequencySetting(const QString &freqText, const QString &sysfsPath, const QString &componentName);
    void setupResourceMonitor();
    void teardownResourceMonitor();
    void updateTemperatureDisplay();
    bool readTemperatureValue(const QString &path, double &valueCelsius);
    bool readMemoryUsageViaFree(double &usedPercent, double &usedMB, double &totalMB);
    bool readNpuLoadInfo(QString &resultLine);
    bool readDdrLoadInfo(QString &resultLine);
    bool readCpuUsageLineViaTop(QString &cpuLine);
    QString runCommandAndCapture(const QString &program, const QStringList &arguments, int timeoutMs = 1500) const;
    QString runShellCommand(const QString &command, int timeoutMs = 1500) const;
    void appendLogLine(const QString &line);
    void updateLabelInfoText(const QString &text, bool forceLog = false);
    static void qtLogProxy(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    bool loadFocalConfigFromFile();
    bool updateFocalParamsForResolution(const QSize &resolution);
    void applyCurrentFocalSetting();
    QString buildResolutionKey(const QSize &resolution) const;
    bool persistFocalParamsForResolution(const QString &resolutionKey, const FocalParams &params);

    Ui::distance *ui;
    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera = nullptr;   // 相机

    QVideoProbe *probe = nullptr;   // 用来接收每帧
    QLabel *displayLabel = nullptr; // 显示处理后帧
    QDialog *keyboardDialog = nullptr;
    VirtualKeyboardFilter *keyboardFilter = nullptr;
    QLineEdit *activeLineEdit = nullptr;
    QTimer *resourceTimer = nullptr;
    bool cpuStatInitialized = false;
    quint64 lastTotalCpuTime = 0;
    quint64 lastIdleCpuTime = 0;

    rknn_app_context_t rknn_app_ctx; // 模型上下文移到成员，保持可用性
    bool convertNV12ToImageBufferSimple(QVideoFrame &frame, image_buffer_t *image_buf);
    void rotateNV12Frame180(image_buffer_t *image_buf);
    QString formatDistanceText(double distanceMeters) const;
    void startDetection();

    void stopDetection();
    void releaseCameraResources();
    int getTargetHeightPx(const object_detect_result &det) const;
    bool detectionRunning = false;

    int m_index = 0;
    int maxIndex = 0;
    double hx_W = 100.0;        // 当前目标先验尺寸，单位 mm
    double hx_f = 600.0;        // 当前像素焦距
    double hx_cor_dist = 600.0; // 当前校正距离
    double camH = 65.0;         // 当前相机高度，单位 mm
    int lastTargetHeightPx = 0;
    QStringList logBuffer;
    QString lastLabelInfoEntry;
    static constexpr int kMaxLogLines = 80;
    static constexpr int kVisibleLogLines = 12;
    static distance *s_logReceiver;
    static QtMessageHandler s_prevHandler;
    static QMutex s_logMutex;
    bool useCalibratedFocal = false;
    bool focalConfigLoaded = false;
    QHash<QString, FocalParams> focalConfig;
    QSize currentResolution = QSize(640, 480);
    FocalParams currentFocalParams;
    QString focalConfigPath;
    bool showCrosshair = false;
    bool distanceFilterActive = false;
    QVector<double> filterSamples;
    static constexpr int kFilterSampleCount = 100;
    double filteredDistanceMeters = 0.0;
};
#endif
