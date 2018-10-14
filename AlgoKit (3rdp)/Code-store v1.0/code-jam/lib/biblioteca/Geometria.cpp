<===============================>
<                 GEOMETRICOS                    >
<===============================>

struct Ponto{
     double x,y;
 
     Ponto(double x = 0, double y = 0) : x(x), y(y){}
 
    //produto interno 2D
     double operator *(Ponto p){
          return x*p.x + y*p.y;
     }
 
    //produto vetorial 2D (lembrar de colocar o 3D)
     double operator %(Ponto p){
          return x*p.y - y*p.x;
     }
 
     Ponto operator - (Ponto p){
      return Ponto(x-p.x, y-p.y);
     }
    
    Ponto operator + (Ponto p){
      return Ponto(x+p.x, y+p.y);
     }
 
    double operator ! (){
      return sqrt(x*x + y*y);
     }
 
    double dist(Ponto p){
      return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
     }
};
 
 struct Seg{
     Point ini, fim;
     
     Seg(Point a = Point(), Point b = Point()) : ini(a), fim(b){}
 
    //usar apenas  quando o ponto a for colinear ao segmento
    bool pertence(Point a){
          return a.x >= min(ini.x, fim.x) && a.x <= max(ini.x, fim.x)
               && a.y >= min(ini.y, fim.y) && a.y <= max(ini.y, fim.y);
     }
 
    //verifica  se dois segmentos se intersectam
     bool inter(Seg s){
      double d1 = (s.ini - ini)%(fim - ini);
      double d2 = (s.fim - ini)%(fim - ini);
      double d3 = (ini - s.ini)%(s.fim - s.ini);
      double d4 = (fim - s.ini)%(s.fim - s.ini);
      if(((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && 
           ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0)))return true;
 
      if(!cmp(d1) && pertence(s.ini))return true;
      if(!cmp(d2) && pertence(s.fim))return true;
      if(!cmp(d3) && s.pertence(ini))return true;
      if(!cmp(d4) && s.pertence(fim))return true; 
         
      return false;
     }
 
    //calcula distância de ponto a segmento
    double dist(Point p){
          if((fim - ini)*(p - fim) >0)return p.dist(fim);
          if((ini - fim)*(p - ini) > 0)return p.dist(ini);
          return (fabs((p-ini)%(fim - ini)))/!(fim - ini);
     }
 
};


//algoritmo místico da biblioteca da PUC
Ponto findCircumcenter(Ponto p1, Ponto p2, Ponto p3){
    Ponto a, b, c;
    a = p1 - p3;
    b = p2 - p3;
    c = Ponto(a*(p1+p3)/2, b*(p2+p3)/2);
   
    return Ponto(c%Ponto(a.y,b.y), Ponto(a.x, b.x)%c)/(a%b);   
}

void minimumSpanningCircle(){
    Circle c(Ponto(), -100000000);
   
    random_shuffle(pontos, pontos + n);
   
    for(int i = 0; i < n ; i++){
        if(!c.pert(pontos[i])){
            c = Circle(pontos[i], 0);
            for(int j = 0;j < i; j++){
                if(!c.pert(pontos[j])){
                    c = Circle((pontos[j] + pontos[i])/2, pontos[j].dist(pontos[i])/2);
                    for(int k = 0; k < j; k++){
                        if(!c.pert(pontos[k])){
                            c.centro = findCircumcenter(pontos[k], pontos[i], pontos[j]);
                            c.raio = c.centro.dist(pontos[k]);
                        }
                    }
                }
            }
        }
    }
}

