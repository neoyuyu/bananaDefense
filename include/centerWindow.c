// Esta funcao centraliza a janela ao centro da tela

void centerWindow(float windowWidth, float windowHeight)
{
    int monitor = GetCurrentMonitor();              // Captura o monitor usado
    int monitor_width = GetMonitorWidth(monitor);   //  Verifica a largura do monitor usado
    int monitor_height = GetMonitorHeight(monitor); //  Verifica a altura do monitor usado

    //  Define a posição da janela (window) na tela/monitor usado ao aproximar para inteiro divido pela metade
    SetWindowPosition((int)(monitor_width / 2) - (int)(windowWidth / 2), (int)(windowHeight / 2) - (int)(windowHeight / 2));
}