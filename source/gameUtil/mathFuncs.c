double getAngleBetweenPoints(double x1, double y1, double x2, double y2) {

    double deltaY = y2 - y1;
    double deltaX = x2 - x1;
    
    double anguloRad = atan2(deltaY, deltaX);
    
    double anguloGraus = anguloRad * 180.0 / PI;
    
    if (anguloGraus < 0) {
        anguloGraus += 360.0;
    }
    
    return anguloGraus;
}


Vector2 getVectorByAngleDistance(double angulo, double distancia) {

    double anguloRad = angulo * PI / 180.0;
    
    Vector2 pos;

    pos.x = distancia * cos(anguloRad);
    pos.y = distancia * sin(anguloRad);

    return pos;
}

double getDistanceBetweenPoints(double x1, double y1, double x2, double y2) {
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    
    // Usando o teorema de Pitágoras para calcular a distância
    double distancia = sqrt(deltaX * deltaX + deltaY * deltaY);
    
    return distancia;
}