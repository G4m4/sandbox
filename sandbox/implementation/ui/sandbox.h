#include <QMainWindow>
#include <QTimer>

namespace Ui {
class Sandbox;
}

namespace sandbox {
namespace dummygroup {
class DummyClass;
}
}

class Sandbox : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sandbox(QWidget* parent = 0);
    ~Sandbox();

private slots:
    void on_quitButton_clicked();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    // Timer update
    void update();
    void processing_end();

private:
    Ui::Sandbox* ui;
    QTimer* ui_timer_;
    QTimer* timer_;
    QScopedPointer<sandbox::dummygroup::DummyClass> dummy_class_instance_;
};
