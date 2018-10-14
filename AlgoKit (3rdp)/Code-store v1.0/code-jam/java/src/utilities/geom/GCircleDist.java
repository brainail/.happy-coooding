package utilities.geom;

public class GCircleDist
{
    static double greatCircleDistance(
        double latitudeS,
        double longitudeS,
        double latitudeF,
        double longitudeF,
        double r)
    {
        latitudeS = Math.toRadians(latitudeS);
        latitudeF = Math.toRadians(latitudeF);
        longitudeS = Math.toRadians(longitudeS);
        longitudeF = Math.toRadians(longitudeF);
        double deltaLongitude = longitudeF - longitudeS;
        double a = Math.cos(latitudeF) * Math.sin(deltaLongitude);
        double b = Math.cos(latitudeS) * Math.sin(latitudeF);
        b -= Math.sin(latitudeS) * Math.cos(latitudeF)
                        * Math.cos(deltaLongitude);
        double c = Math.sin(latitudeS) * Math.sin(latitudeF);
        c += Math.cos(latitudeS) * Math.cos(latitudeF)
                        * Math.cos(deltaLongitude);
        return Math.atan(Math.sqrt(a * a + b * b) / c) * r;
    }

    public static void main(String[] args)
    {
        System.out.println(greatCircleDistance(46, 87, 40, 89, 25000));
    }
}
