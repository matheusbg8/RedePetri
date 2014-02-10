#include "EditorVariaveis.h"
#include "ui_EditorVariaveis.h"

EditorVariaveis::EditorVariaveis(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::EditorVariaveis)
{
    ui->setupUi(this);
}

EditorVariaveis::~EditorVariaveis()
{
    delete ui;
}
