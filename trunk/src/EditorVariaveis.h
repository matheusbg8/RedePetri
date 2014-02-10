#ifndef EDITORVARIAVEIS_H
#define EDITORVARIAVEIS_H

#include <QDockWidget>

namespace Ui {
class EditorVariaveis;
}

class EditorVariaveis : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit EditorVariaveis(QWidget *parent = 0);
    ~EditorVariaveis();
    
private:
    Ui::EditorVariaveis *ui;
};

#endif // EDITORVARIAVEIS_H
