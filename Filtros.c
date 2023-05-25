/*
 * DCE05968 - Estruturas de Dados I
 * Funções responsaveis pelos filtros que podem ser aplicados na imagem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Filtros.h" /* Protótipo das funções responsáveis pelos filtros das imagens */

/* Função responsável por escurecer uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/escurece 
 * cada um de seus pixels em cada canal de cor (RGB).
 * 
 * Analise essa função com bastante atenção. Ela irá te auxiliar no entendimento 
 * do TAD Imagem e como outros filtros podem ser implementados.
 *
 * Você não precisa modificar essa função 
 */
void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);
    /* Cada canal de cor (RGB) de cada pixel é reduzido 'v' do valor.
     * Note que devemos garantir que o valor esteja entre 0 e 255.   
     * Como estamos subtraindo, verificamos apenas se o valor é >= 0 
     * Note também a utilização de expressão ternária e o cast (conversão) 
     * entre os valores Byte (unsigned int) e int. Esse cast evita erros nas 
     * operações matemáticas.
     */ 
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem 
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] - v) >= 0 ? ((int)pixel.cor[RED] - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? ((int)pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] - v) >= 0 ? ((int)pixel.cor[BLUE] - v) : 0);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por clarear uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/clareia 
 * cada um de seus pixels em cada canal de cor (RGB).
 */
void clarearImagem(Imagem *img){
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem 
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] + v) <= 255 ? ((int)pixel.cor[RED] + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? ((int)pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] + v) <= 255 ? ((int)pixel.cor[BLUE] + v) : 255);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por converter uma imagem colorida em escala de cinza
 * A função recebe um ponteiro para um struct Imagem e converte 
 * cada um de seus pixels em cada canal de cor (RGB) em uma tonalidade de cinza.
 * 
 * No pdf de descrição do EP existem duas estretégias para a implementação 
 * desse filtro. Você deve implementar uma delas ou pesquisar por outras alternativas. 
 */
void escalaDeCinzaImagem(Imagem *img){
    int v;
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img,h,w);
            v = (0.3 * (int)pixel.cor[RED] + 0.59 * (int)pixel.cor[GREEN] + 0.11 * (int)pixel.cor[BLUE]);
            if(v<0)
                v = 0;
            else if(v>255)
                v = 255;
            pixel.cor[RED]   = v;
            pixel.cor[GREEN] = v;
            pixel.cor[BLUE]  = v;
            recolorePixel(img, h, w, pixel);

        }
    }
}

/* Função responsável por aplicar o filtro de Sobel na imagem. 
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado. 
 */
void filtroSobel(Imagem *img){
    int r_y,r_x,g_y,g_x,b_y,b_x,r,g,b;

    Imagem *copia = copiaImagem(img);
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            
            Pixel pixel = obtemPixel(img,h,w);
            
            //matriz y

            r_y = (((int)obtemPixel(copia,h-1,w-1).cor[RED] *(1)) + ((int)obtemPixel(copia,h-1,w).cor[RED] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[RED] *(1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[RED] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[RED] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[RED] *(-1)) );

            g_y = (((int)obtemPixel(copia,h-1,w-1).cor[GREEN] *(1)) + ((int)obtemPixel(copia,h-1,w).cor[GREEN] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[GREEN] *(1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[GREEN] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[GREEN] *(-1)));
        
            b_y = (((int)obtemPixel(copia,h-1,w-1).cor[BLUE] *(1)) + ((int)obtemPixel(copia,h-1,w).cor[BLUE] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[BLUE] *(1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[BLUE] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[BLUE] *(-1)));                   
            
            //matriz x
            
            
            r_x = (((int)obtemPixel(copia,h-1,w-1).cor[RED] *(1)) + ((int)obtemPixel(copia,h,w-1).cor[RED] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[RED] *(-1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[RED] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[RED] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[RED] *(-1)) );

            g_x = (((int)obtemPixel(copia,h-1,w-1).cor[GREEN] *(1)) + ((int)obtemPixel(copia,h,w-1).cor[GREEN] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[GREEN] *(-1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[GREEN] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[GREEN] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[GREEN] *(-1)) );
        
            b_x = (((int)obtemPixel(copia,h-1,w-1).cor[BLUE] *(1)) + ((int)obtemPixel(copia,h,w-1).cor[BLUE] *(2) )+ ((int)obtemPixel(copia,h-1,w+1).cor[BLUE] *(-1)) + 
            ((int)obtemPixel(copia,h+1,w-1).cor[BLUE] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[BLUE] *(-2)) + ((int)obtemPixel(copia,h+1,w+1).cor[BLUE] *(-1)) );

            r = (r_x + r_y) / 2;
            g = (g_x + g_y) / 2;
            b = (b_x + b_y) / 2;
            
            
            
            
            
            
            
            pixel.cor[RED]   = r >= 255 ? 255 : r <= 0 ? 0 : r;
            pixel.cor[GREEN] = g >= 255 ? 255 : g <= 0 ? 0 : g;
            pixel.cor[BLUE]  = b >= 255 ? 255 : b <= 0 ? 0 : b;
            recolorePixel(img, h, w, pixel);
        
        }
    }
    liberaImagem(copia);
    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy 
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem. 
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */
}

/* Função responsável por aplicar a detecçõa de bordas de Laplace na imagem. 
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado. 
 */
void deteccaoBordasLaplace(Imagem *img) {

    int r,g,b;

    Imagem *copia= copiaImagem(img);
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            
            Pixel pixel = obtemPixel(img,h,w);
            

            r = (((int)obtemPixel(copia,h-1,w).cor[RED] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[RED] *(-1) )+ ((int)obtemPixel(copia,h,w-1).cor[RED] *(-1)) + 
            ((int)obtemPixel(copia,h,w+1).cor[RED] *(-1)) + ((int)obtemPixel(copia,h,w).cor[RED] *(4)));

            g = (((int)obtemPixel(copia,h-1,w).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[GREEN] *(-1)) + 
            ((int)obtemPixel(copia,h,w-1).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h,w+1).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h,w).cor[GREEN] *(4)));
        
            b = (((int)obtemPixel(copia,h-1,w).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h+1,w).cor[BLUE] *(-1)) + 
            ((int)obtemPixel(copia,h,w-1).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h,w+1).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h,w).cor[BLUE] *(4)));                   
            
            
            pixel.cor[RED]   = r >= 255 ? 255 : r <= 0 ? 0 : r;
            pixel.cor[GREEN] = g >= 255 ? 255 : g <= 0 ? 0 : g;
            pixel.cor[BLUE]  = b >= 255 ? 255 : b <= 0 ? 0 : b;
            recolorePixel(img, h, w, pixel);
        
        }
    }
    liberaImagem(copia);

}


/* Função responsável por aplicar na imagem o filtro definido por você. Seja criativo! 
 * Filtros que apenas fazem algumas modificações simples em cada pixel 
 * (por exemplo, negativo, espelhar a imagem) não serão considerados.
 */


void desfoca(Imagem *img){
    int r,g,b;

    Imagem *copia= copiaImagem(img);
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            
            Pixel pixel = obtemPixel(img,h,w);
            

            r = (((int)obtemPixel(copia,h-1,w-1).cor[RED] *(0.11)) + ((int)obtemPixel(copia,h-1,w).cor[RED] *(0.11) )+ ((int)obtemPixel(copia,h-1,w+1).cor[RED] *(0.11)) + 
            ((int)obtemPixel(copia,h,w-1).cor[RED] *(0.11)) + ((int)obtemPixel(copia,h,w).cor[RED] *(0.11)) + (int)obtemPixel(copia,h,w+1).cor[RED] *(0.11) + 
            (int)obtemPixel(copia,h+1,w-1).cor[RED] *(0.11) + (int)obtemPixel(copia,h+1,w).cor[RED] *(0.11) + (int)obtemPixel(copia,h+1,w+1).cor[RED] *(0.11));

            g = ((((int)obtemPixel(copia,h-1,w-1).cor[GREEN] *(0.11)) + ((int)obtemPixel(copia,h-1,w).cor[GREEN] *(0.11) )+ ((int)obtemPixel(copia,h-1,w+1).cor[GREEN] *(0.11)) + 
            ((int)obtemPixel(copia,h,w-1).cor[GREEN] *(0.11)) + ((int)obtemPixel(copia,h,w).cor[GREEN] *(0.11)) + (int)obtemPixel(copia,h,w+1).cor[GREEN] *(0.11) + 
            (int)obtemPixel(copia,h+1,w-1).cor[GREEN] *(0.11) + (int)obtemPixel(copia,h+1,w).cor[GREEN] *(0.11) + (int)obtemPixel(copia,h+1,w+1).cor[GREEN] *(0.11)));
        
            b = (((int)obtemPixel(copia,h-1,w-1).cor[BLUE] *(0.11)) + ((int)obtemPixel(copia,h-1,w).cor[BLUE] *(0.11) )+ ((int)obtemPixel(copia,h-1,w+1).cor[BLUE] *(0.11)) + 
            ((int)obtemPixel(copia,h,w-1).cor[BLUE] *(0.11)) + ((int)obtemPixel(copia,h,w).cor[BLUE] *(0.11)) + (int)obtemPixel(copia,h,w+1).cor[BLUE] *(0.11) + 
            (int)obtemPixel(copia,h+1,w-1).cor[BLUE] *(0.11) + (int)obtemPixel(copia,h+1,w).cor[BLUE] *(0.11) + (int)obtemPixel(copia,h+1,w+1).cor[BLUE] *(0.11));                   
            
            
            pixel.cor[RED]   = r >= 255 ? 255 : r <= 0 ? 0 : r;
            pixel.cor[GREEN] = g >= 255 ? 255 : g <= 0 ? 0 : g;
            pixel.cor[BLUE]  = b >= 255 ? 255 : b <= 0 ? 0 : b;
            recolorePixel(img, h, w, pixel);
        
        }
    }
    liberaImagem(copia);
}
void negativa(Imagem *img){
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem 
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (255 - (int)pixel.cor[RED] );
            pixel.cor[GREEN] = (255 - (int)pixel.cor[GREEN] );
            pixel.cor[BLUE]  = (255 - (int)pixel.cor[BLUE] );
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

void destaqueRelevo(Imagem *img){
int r,g,b;

    Imagem *copia= copiaImagem(img);
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            
            Pixel pixel = obtemPixel(img,h,w);
            

            r = (((int)obtemPixel(copia,h-1,w-1).cor[RED] *(-2)) + ((int)obtemPixel(copia,h-1,w).cor[RED] *(-1) ) + 
            ((int)obtemPixel(copia,h,w-1).cor[RED] *(-1)) + ((int)obtemPixel(copia,h,w).cor[RED] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[RED] *(1))
             + (int)obtemPixel(copia,h+1,w).cor[RED] *(1) + ((int)obtemPixel(copia,h+1,w+1).cor[RED] *(2)));

            g = (((int)obtemPixel(copia,h-1,w-1).cor[GREEN] *(-2)) + ((int)obtemPixel(copia,h-1,w).cor[GREEN] *(-1) ) + 
            ((int)obtemPixel(copia,h,w-1).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h,w).cor[GREEN] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[GREEN] *(1))
             + (int)obtemPixel(copia,h+1,w).cor[GREEN] *(1) + ((int)obtemPixel(copia,h+1,w+1).cor[GREEN] *(2)));
        
            b = (((int)obtemPixel(copia,h-1,w-1).cor[BLUE] *(-2)) + ((int)obtemPixel(copia,h-1,w).cor[BLUE] *(-1) ) + 
            ((int)obtemPixel(copia,h,w-1).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h,w).cor[BLUE] *(1)) + ((int)obtemPixel(copia,h,w+1).cor[BLUE] *(1))
             + (int)obtemPixel(copia,h+1,w).cor[BLUE] *(1) + ((int)obtemPixel(copia,h+1,w+1).cor[BLUE] *(2)));                   
            
            
            pixel.cor[RED]   = r >= 255 ? 255 : r <= 0 ? 0 : r;
            pixel.cor[GREEN] = g >= 255 ? 255 : g <= 0 ? 0 : g;
            pixel.cor[BLUE]  = b >= 255 ? 255 : b <= 0 ? 0 : b;
            recolorePixel(img, h, w, pixel);
        
        }
    }
    liberaImagem(copia);

}
void meuFiltro(Imagem *img){
    int r,g,b;
    //deixa a imagem mais nitida
    Imagem *copia= copiaImagem(img);
    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++){
            
            Pixel pixel = obtemPixel(img,h,w);
            

            r = (((int)obtemPixel(copia,h-1,w-1).cor[RED] *(0)) + ((int)obtemPixel(copia,h-1,w).cor[RED] *(-1) )+ ((int)obtemPixel(copia,h-1,w+1).cor[RED] *(0)) + 
            ((int)obtemPixel(copia,h,w-1).cor[RED] *(-1)) + ((int)obtemPixel(copia,h,w).cor[RED] *(5)) + (int)obtemPixel(copia,h,w+1).cor[RED] *(-1) + 
            (int)obtemPixel(copia,h+1,w-1).cor[RED] *(0) + (int)obtemPixel(copia,h+1,w).cor[RED] *(-1) + (int)obtemPixel(copia,h+1,w+1).cor[RED] *(0));

            g = (((int)obtemPixel(copia,h-1,w-1).cor[GREEN] *(0)) + ((int)obtemPixel(copia,h-1,w).cor[GREEN] *(-1) )+ ((int)obtemPixel(copia,h-1,w+1).cor[GREEN] *(0)) + 
            ((int)obtemPixel(copia,h,w-1).cor[GREEN] *(-1)) + ((int)obtemPixel(copia,h,w).cor[GREEN] *(5)) + (int)obtemPixel(copia,h,w+1).cor[GREEN] *(-1) + 
            (int)obtemPixel(copia,h+1,w-1).cor[GREEN] *(0) + (int)obtemPixel(copia,h+1,w).cor[GREEN] *(-1) + (int)obtemPixel(copia,h+1,w+1).cor[GREEN] *(0));
        
            b = (((int)obtemPixel(copia,h-1,w-1).cor[BLUE] *(0)) + ((int)obtemPixel(copia,h-1,w).cor[BLUE] *(-1) )+ ((int)obtemPixel(copia,h-1,w+1).cor[BLUE] *(0)) + 
            ((int)obtemPixel(copia,h,w-1).cor[BLUE] *(-1)) + ((int)obtemPixel(copia,h,w).cor[BLUE] *(5)) + (int)obtemPixel(copia,h,w+1).cor[BLUE] *(-1) + 
            (int)obtemPixel(copia,h+1,w-1).cor[BLUE] *(0) + (int)obtemPixel(copia,h+1,w).cor[BLUE] *(-1) + (int)obtemPixel(copia,h+1,w+1).cor[BLUE] *(0));                   
            
            
            pixel.cor[RED]   = r >= 255 ? 255 : r <= 0 ? 0 : r;
            pixel.cor[GREEN] = g >= 255 ? 255 : g <= 0 ? 0 : g;
            pixel.cor[BLUE]  = b >= 255 ? 255 : b <= 0 ? 0 : b;
            recolorePixel(img, h, w, pixel);
        
        }
    }
    liberaImagem(copia);
}