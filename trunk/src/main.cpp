
//#include <QtGui/QApplication>
//#include "ROSBridge/ROSBridge.h"
//using namespace std;

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    RosBridge r;
//    list<string> lista;

//    r.conecta("ws://localhost",9090);
//    a.processEvents();

//    r.criaTopico("/matheus", "std_msgs/String");
//    r.escutaTopico("/matheus");

//    for(int i = 0 ; i < 20 ; i++)
//    {
//        r.publica("/matheus", QString("{\"data\":\"msg %1\"}").arg(i).toStdString());

//        cout << "Consultando lista de topicos" << endl;
////        if(r.listaTopicos(lista))
//        if(r.listaParametros(lista))
//        {
//            cout << "Lista de topicos:" << endl;
//            list<string>::iterator il;
//            for(il = lista.begin(); il != lista.end() ; il++)
//            {
//                cout << (*il) << endl;
//            }
//        }
//        lista.clear();
//        a.processEvents();
////        sleep(1);
//    }
//    a.processEvents();
//}

//#include <QtGui/QApplication>
//#include <list>
//#include <iostream>
//#include <QInputDialog>
//#include "ConfiguracaoAmbienteROS.h"

//using namespace std;

//#include "RetanguloBasico.h"

//int main(int argc, char *argv[])
//{

//    QApplication a(argc, argv);
//    list<string> lista;

//    bool ok;
//    QString endereco = QInputDialog::getText(0x0, QString("Configuracao ROSBridge"), QString("Endereco:"), QLineEdit::Normal, "ws://localhost:9090", &ok);
//    endereco = endereco.trimmed();
//    if (ok && !endereco.isEmpty())
//    {
//        QString ip;
//        quint16 port;
//        if (endereco.contains(QRegExp(QLatin1String(":([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{1,4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"))))
//        {
//            QStringList splitted = endereco.split(':');
//            port = splitted.takeLast().toUInt();
//            ip = splitted.join(":");
//        }
//        else
//        {
//            ip = endereco;
//            port = 80;
//        }
//        cout << "IP: " << ip.toStdString() << " porta " << port << endl;
//    }

//    lista.push_back("Machado1");
//    lista.push_back("Machado2");
//    lista.push_back("Machado3");
//    lista.push_back("Machado4");
//    lista.push_back("Machado5");

//    ConfiguracaoAmbienteROS d(lista);
//    d.exec();

//    cout << "Selecionado:" << endl;
//    list<string>::iterator i;
//    for(i = lista.begin() ; i != lista.end() ; i++)
//    {
//        cout << *i << endl;
//    }

//    return a.exec();
//}


/// @todo - Remover espacos brancos entre expressoes logicas por causa do protocolo de comunicacao

// EEML.org

#include <QtGui/QApplication>
#include "JanelaPrincipal.h"
#include "WidgetProgramacao.h"

#include <iostream>

using namespace std;

#include "RetanguloBasico.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    JanelaPrincipal w;
    w.show();
    return a.exec();
}

///* --- Pagina principal da documentacao link: http://dl.dropbox.com/u/65272659/RedePetriDoc/index.html ------ */

/**
 *  \mainpage Editor de redes de petri.
 *
 * \section sec_introducao Introdução
 *
 *  Esta ferramenta esta sendo desenvolvida para modelar
 * e simular Redes de Petri capazes de resolver problemas
 * de manufatura, e modelar redes para especificação
 * de sistemas multiagentes.
 *
 *  - \subpage pag_imagensAtual "Imagens da ferramenta atual que esta sendo desenvolvida."
 *\n\n Novo:\n
 *  \subpage pag_imagenUML "Diagrama de Classes."
 *
 * \section sec_instalacao Instalação
 *
 *  Atualmente a ferramenta não tem um instalador próprio, para utiliza-la
 * basta baixar <a href="https://dl.dropbox.com/sh/tf4309hkj12aiwp/bZinGH32Mh/RP.zip?dl=1"> este arquivo zip</a>
 * descompactar tudo para uma pasta qualquer, renomear o arquivo RedePetri_exe
 * para RedePetri.exe e executar. Atualmente so existe versão compilada para windows, em breve
 * sera compilado uma versão para linux.
 *
 * \section sec_ajuda Ajuda
 *  Ainda não existe um guia de ajuda da ferramenta, existe apenas
 * algumas demonstrações em video de como a utilizar <a href="http://www.youtube.com/watch?v=MVMoWSI79wM&feature=youtu.be"> AQUI</a>
 * e uma demonstração um pouco mais antiga <a href="http://www.youtube.com/watch?v=Aes3joXePlE"> AQUI</a>.
 * \section sec_vantriores Versão anterior.
 * Uma versão dessa ferramenta foi desenvolvida utilizando a biblioteca gráfica
 * allegro.
 *  - \subpage pag_vanterior "Mais informações sobre a versão em allegro"
 *
 *  Mais alguma coisa...
 */

/* --- Pagina de imagens da versão atual -------------------- */

/* --- Pagina da versão antiga do editor de redes de petri ----- */

/**
 *
 *  \page pag_imagensAtual Imagens atuais da ferramenta.
 * A ferramenta ainda esta em desenvolvimento, portanto a interface gráfica ainda
 * não esta pronta.
 *  A interface gráfica esta sendo desenvolvida utilizando os objetos gráficos do Qt,
 * junto com o seu suporte a OpenGL, QGLWidget.
 *\n
 * A Imagem abaixo demonstra os desenhos primitivos que seram utilizados para desenhar as redes de petri,
 * é possivel ver um container já com alguns desenhos.
 *\n Um circulo, um triangulo, um segmento e um retangulo são os desenhos primitivos.
 *\n O desenho composto é um arco, uma composição de segmento, triangulo e circulo.
 *\n E uma RedePetri, que é uma especialização de um container, com restrições de desenhos que podem ser
 * colocados, permitindo que apenas componentes da Rede de Petri sejam adicionados. Ela também oferece
 * opções especiais para criar e manipular componentes de Redes de Petri.
 *      \image html mnuFundoDesenho.png " Desmonstração dos desenhos primitivos da interface grafica. "
 * A imagem a seguir, mostra várias Redes de Petri no mesmo Container, também mostra um menu especifico
 * para criar componentes para Redes de Petri.
 *      \image html mnuFundoRedePetri.png " Desmonstração do container Rede de Petri. "
 *
**/

/**
 *
 *  \page pag_imagenUML Diagrama UML.
 * Logo abaixo esta o diagrama UML da ferramenta, gerado pelo modelador UML Umbrello.
 *      \image html umlFull.png " Diagrama UML. "
 *
**/

/**
 *
 *  \page pag_vanterior Versões anteriores desenvolvidas.
 *
 *\section sec_introducaoAnt RedePetri com allegro.
 *  Uma versão utilizando apenas a biblioteca gráfica allegro foi desenvolvida.
 *
 *\section sec_imgsAnt Algumas imagens da versão em allegro
 * \subsection subsec_interface Imagens da interface gráfica:
 *      \image html antInterfaceGrafica.png "Interface grafica da ferramenta"
 *\n\n
 *      \image html antAnalise.png " Fazendo Análises da rede. "
 *\n\n
 *      \image html antArquivo.png " Menu Arquivo da interface gráfica. "
 *\n\n
 *      \image html antBalao.png " Balão de informação da transição. "
 *\n\n
 *      \image html antGrafo.png " Grafo de componentes gerado apartir do conjunto de estados alcançável pela rede de petri."
 *\n\n
 *      \image html antImg1.png " Exemplo de uma rede de petri simples."
 *\n\n
 *      \image html antInterface.png " Exemplo de uma Rede Petri maior. "
 *\n\n
 *      \image html antInterface2.png " Exemplo de uma rede de Petri Utilizada para controlar agentes jogadores de futbol. "
 *\n\n
 *      \image html antMenuFundo.png " Menu de fundo."
 *\n\n
 *\subsection subsec_opdebug Opções de depuração:
 *      \image html antImg12.png "Matriz-debug da posição dos componentes da rede de petri anterior."
 *\n\n
 *      \image html antMarcacao.png " Matriz - debug, mostra o vetor de marcação da Rede de Petri."
 *\n\n
 *      \image html antPosterior.png " Matriz - debug, mostra a matriz posterior da Rede de Petri. "
 *\n\n
 *      \image html antPresedencia.png " Matriz - debug, mostra a matriz de prescedencia da Rede de Petri "
 *\n\n
 *
 *\subsection subsec_xml Arquivos XML gerados:
 *      \image html antLugarXML.png " Formato do XML gerado para representar um Lugar da Rede de Petri."
 *\n\n
 *      \image html antRegraXML.png " Formato de uma regra em XML."
 *\n\n
 *      \image html antArcoXML.png " Representação do arco em XML."
 *\n\n
 *      \image html antBaseRegrasxml2.png " Base de regras gerado em XML."
 *\n\n
 *      \image html antTransicaoXML.png " Formato de uma Transição em XML."
 *\n\n
 *      \image html antXML2.png " Formato de uma Rede de Petri em XML."
**/

