#ifndef FONT_H
#define FONT_H

#include <QDialog>

namespace Ui {
class Font;
}

class Font : public QDialog
{
    Q_OBJECT

public:
    explicit Font(QWidget *parent = nullptr);
    ~Font();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Font *ui;
};

#endif // FONT_H
