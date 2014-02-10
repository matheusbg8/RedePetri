#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T10:33:24
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += xml
QT += network


TARGET = RedePetri
TEMPLATE = app

INCLUDEPATH += Ambiente \
    Automato \
    Grafo \
    InterfaceGrafica \
    Linguagem \
    Matriz \
    RedePetri \
    RedePetri/RedePetriEstrutura \
    QtWebsocket


SOURCES += main.cpp \
    Ambiente/VariavelAmbiente.cpp \
    Ambiente/PerguntaAmbiente.cpp \
    Ambiente/NodoAmbiente.cpp \
    Ambiente/DVariavelAmbiente.cpp \
    Ambiente/DAmbiente.cpp \
    Ambiente/CAmbiente.cpp \
    Ambiente/AcaoAmbiente.cpp \
    Automato/Automato.cpp \
    Automato/ArestaAutomato.cpp \
    Grafo/VisualizadorGrafo.cpp \
    Grafo/VerticeGrafo.cpp \
    Grafo/GrafoNome.cpp \
    Grafo/GrafoMatriz.cpp \
    Grafo/GrafoLista.cpp \
    Grafo/Grafo.cpp \
    Grafo/DVertice.cpp \
    Grafo/DGrafo.cpp \
    Grafo/DAresta.cpp \
    Grafo/ArestaGrafo.cpp \
    InterfaceGrafica/VisualizadorPropriedades.cpp \
    InterfaceGrafica/Utilidades.cpp \
    InterfaceGrafica/TrianguloModificavel.cpp \
    InterfaceGrafica/TrianguloBasico.cpp \
    InterfaceGrafica/Triangulo.cpp \
    InterfaceGrafica/Seta.cpp \
    InterfaceGrafica/Segmento.cpp \
    InterfaceGrafica/RetanguloBasico.cpp \
    InterfaceGrafica/Retangulo.cpp \
    InterfaceGrafica/PosicionadorObjetos2D.cpp \
    InterfaceGrafica/Ponto.cpp \
    InterfaceGrafica/Poligono.cpp \
    InterfaceGrafica/GerenciadorNomes.cpp \
    InterfaceGrafica/GerenciadorElementos.cpp \
    InterfaceGrafica/DesenhoMestre.cpp \
    InterfaceGrafica/DesenhoComposto.cpp \
    InterfaceGrafica/Desenho.cpp \
    InterfaceGrafica/Cor.cpp \
    InterfaceGrafica/Container.cpp \
    InterfaceGrafica/CirculoBasico.cpp \
    InterfaceGrafica/AreaDesenho.cpp \
    Linguagem/LivroLiterais.cpp \
    Linguagem/LiteralVariavel.cpp \
    Linguagem/LiteralString.cpp \
    Linguagem/LiteralOperador.cpp \
    Linguagem/LiteralNumero.cpp \
    Linguagem/LiteralGenerico.cpp \
    Linguagem/LiteralBooleano.cpp \
    Linguagem/Literal.cpp \
    Matriz/Matriz.cpp \
    RedePetri/Transicao.cpp \
    RedePetri/RedePetri.cpp \
    RedePetri/ModeloGrafoSimples.cpp \
    RedePetri/Lugar.cpp \
    RedePetri/DTransicao.cpp \
    RedePetri/DRedePetri.cpp \
    RedePetri/DLugar.cpp \
    RedePetri/DArco.cpp \
    RedePetri/ComponentePetri.cpp \
    RedePetri/Arco.cpp \
    WidgetProgramacao.cpp \
    WidgetDesenho.cpp \
    TransicaoAbstrata.cpp \
    SegmentoAjustavel.cpp \
    Reta.cpp \
    mouseevento.cpp \
    meuobjeto.cpp \
    ListaDesenhos.cpp \
    JanelaPrincipal.cpp \
    EventoDeseho.cpp \
    Evento.cpp \
    EscutaMouse.cpp \
    EscutaEventoMouse.cpp \
    EditorVariaveis.cpp \
    DNovoAmbiente.cpp \
    DialogNovaVariavelAmbiente.cpp \
    DialogGrafoCobertura.cpp \
    DesenhoLingavel.cpp \
    Controle.cpp \
    Arvore.cpp \
    sinal.cpp \
    RedePetri/JogadorRede.cpp \
    RedePetri/ControladorRede.cpp \
    Ambiente/Ambiente.cpp \
    Linguagem/Expressao.cpp \
    Ambiente/IAmbiente.cpp \
    Ambiente/NodoAmbiente2.cpp \
    RedePetri/IRedepetri.cpp \
    RedePetri/IVRedePetri.cpp \
    ComunicadorTCP.cpp \
    RedePetri/ComunicadorRedePetri.cpp \
    Ambiente/AcaoLocal.cpp \
    RedePetri/DJogadorRede.cpp \
    DialogNovoNodoAmbiente.cpp \
    RedePetri/DRedeAmbiente.cpp \
    InterfaceGrafica/DesenhoGenerico.cpp \
    InterfaceGrafica/ContainerGenerico.cpp \
    DialogGenerico.cpp \
    Ambiente/DPergunta.cpp \
    Ambiente/DNodo.cpp \
    Ambiente/AmbienteExterno.cpp \
    InterfaceGrafica/TesteContainerGenerico.cpp \
    InterfaceGrafica/DesenhoDeLigacao.cpp \
    InterfaceGrafica/SegmentoBasico.cpp \
    EscutaComunicadorTCP.cpp \
    Ambiente/AmbienteExternoROSBridge.cpp \
    WebSocket.cpp \
    QtWebsocket/QWsSocket.cpp \
    QtWebsocket/QWsServer.cpp \
    QtWebsocket/QWsHandshake.cpp \
    QtWebsocket/QWsFrame.cpp \
    QtWebsocket/QTlsServer.cpp \
    QtWebsocket/functions.cpp \
    QtWebsocket/Client/Client.cpp \
    ROSBridge/ROSBridge.cpp \
    ROSBridge/EscutaRosBridge.cpp \
    ROSBridge/MensagemROS.cpp \
    FilaCircular.cpp \
    ROSBridge/ROSBridgeJSON.cpp \
    ConfiguracaoAmbienteROS.cpp
#    RedePetri/RedePetriEstrutura/RedePetriEstrutura.cpp

HEADERS  += JanelaPrincipal.h \
    Ambiente/VariavelAmbiente.h \
    Ambiente/PerguntaAmbiente.h \
    Ambiente/NodoAmbiente.h \
    Ambiente/DVariavelAmbiente.h \
    Ambiente/DAmbiente.h \
    Ambiente/CAmbiente.h \
    Ambiente/AcaoAmbiente.h \
    Automato/Automato.h \
    Automato/ArestaAutomato.h \
    Grafo/VisualizadorGrafo.h \
    Grafo/VerticeGrafo.h \
    Grafo/GrafoNome.h \
    Grafo/GrafoMatriz.h \
    Grafo/GrafoLista.h \
    Grafo/Grafo.h \
    Grafo/DVertice.h \
    Grafo/DGrafo.h \
    Grafo/DAresta.h \
    Grafo/ArestaGrafo.h \
    InterfaceGrafica/VisualizadorPropriedades.h \
    InterfaceGrafica/Utilidades.h \
    InterfaceGrafica/TrianguloModificavel.h \
    InterfaceGrafica/TrianguloBasico.h \
    InterfaceGrafica/Triangulo.h \
    InterfaceGrafica/TipoDesenho.h \
    InterfaceGrafica/Seta.h \
    InterfaceGrafica/Segmento.h \
    InterfaceGrafica/RetanguloBasico.h \
    InterfaceGrafica/Retangulo.h \
    InterfaceGrafica/PosicionadorObjetos2D.h \
    InterfaceGrafica/Ponto.h \
    InterfaceGrafica/Poligono.h \
    InterfaceGrafica/GerenciadorNomes.h \
    InterfaceGrafica/GerenciadorElementos.h \
    InterfaceGrafica/DesenhoMestre.h \
    InterfaceGrafica/DesenhoComposto.h \
    InterfaceGrafica/Desenho.h \
    InterfaceGrafica/Cor.h \
    InterfaceGrafica/Container.h \
    InterfaceGrafica/CirculoBasico.h \
    InterfaceGrafica/AreaDesenho.h \
    Linguagem/LivroLiterais.h \
    Linguagem/LiteralVariavel.h \
    Linguagem/LiteralString.h \
    Linguagem/LiteralOperador.h \
    Linguagem/LiteralNumero.h \
    Linguagem/LiteralGenerico.h \
    Linguagem/LiteralBooleano.h \
    Linguagem/Literal.h \
    Matriz/Matriz.h \
    RedePetri/Transicao.h \
    RedePetri/RedePetri.h \
    RedePetri/ModeloGrafoSimples.h \
    RedePetri/ModeloGrafo.h \
    RedePetri/Lugar.h \
    RedePetri/DTransicao.h \
    RedePetri/DRedePetri.h \
    RedePetri/DLugar.h \
    RedePetri/DArco.h \
    RedePetri/ComponentePetri.h \
    RedePetri/Arco.h \
    WidgetProgramacao.h \
    WidgetDesenho.h \
    TransicaoAbstrata.h \
    SegmentoAjustavel.h \
    Reta.h \
    Observer.h \
    mouseevento.h \
    meuobjeto.h \
    ListaDesenhos.h \
    EventoDeseho.h \
    Evento.h \
    EscutaMouse.h \
    EscutaEventoMouse.h \
    EditorVariaveis.h \
    DNovoAmbiente.h \
    DialogNovaVariavelAmbiente.h \
    DialogGrafoCobertura.h \
    DesenhoLingavel.h \
    Desenhista.h \
    Definicoes.h \
    DComponentePetri.h \
    Controle.h \
    Arvore.h \
    sinal.h \
    RedePetri/JogadoRrede.h \
    RedePetri/ControladorRede.h \
    RedePetri/RedePetriAbstrata.h \
    Ambiente/Ambiente.h \
    Ambiente/Ambiente.h \
    Linguagem/Expressao.h \
    Ambiente/IAmbiente.h \
    Ambiente/NodoAmbiente2.h \
    RedePetri/IRedepetri.h \
    RedePetri/IVRedePetri.h \
    ComunicadorTCP.h \
    RedePetri/ComunicadorRedePetri.h \
    Ambiente/AcaoLocal.h \
    RedePetri/DJogadorRede.h \
    DialogNovoNodoAmbiente.h \
    RedePetri/DRedeAmbiente.h \
    RedePetri/EscutaJogadorRede.h \
    Ambiente/VisualizacaoAmbiente.h \
    InterfaceGrafica/DesenhoGenerico.h \
    InterfaceGrafica/ContainerGenerico.h \
    DialogGenerico.h \
    Ambiente/DPergunta.h \
    Ambiente/DNodo.h \
    Ambiente/AmbienteExterno.h \
    InterfaceGrafica/TesteContainerGenerico.h \
    InterfaceGrafica/DesenhoDeLigacao.h \
    InterfaceGrafica/SegmentoBasico.h \
    EscutaComunicadorTCP.h \
    Ambiente/AmbienteExternoROSBridge.h \
    WebSocket.h \
    QtWebsocket/WsEnums.h \
    QtWebsocket/QWsSocket.h \
    QtWebsocket/QWsServer.h \
    QtWebsocket/QWsHandshake.h \
    QtWebsocket/QWsFrame.h \
    QtWebsocket/QTlsServer.h \
    QtWebsocket/functions.h \
    QtWebsocket/Client/Client.h \
    ROSBridge/ROSBridge.h \
    ROSBridge/EscutaRosBridge.h \
    ROSBridge/MensagemROS.h \
    FilaCircular.h \
    ROSBridge/ROSBridgeJSON.h \
    ConfiguracaoAmbienteROS.h
#    RedePetri/RedePetriEstrutura/RedePetriEstrutura.h

FORMS    += JanelaPrincipal.ui \
    WidgetProgramacao.ui \
    EditorVariaveis.ui \
    DNovoAmbiente.ui \
    DialogNovaVariavelAmbiente.ui \
    DialogGrafoCobertura.ui \
    DialogNovoNodoAmbiente.ui \
    DialogGenerico.ui \
    QtWebsocket/Client/Client.ui \
    ConfiguracaoAmbienteROS.ui

OTHER_FILES += \
    ANOTACOES.txt \
    PerguntasModeloUML.txt
