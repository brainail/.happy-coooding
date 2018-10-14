package utilities.geom;

import java.awt.geom.*;
import java.util.*;

public class BoxUnion
{
    private Rectangle2D[] rects;

    public int area(String[] rectangles)
    {
        rects = new Rectangle2D[rectangles.length];
        for (int i = 0; i < rectangles.length; i++) {
            StringTokenizer st = new StringTokenizer(rectangles[i]);
            double left = Double.parseDouble(st.nextToken());
            double bottom = Double.parseDouble(st.nextToken());
            double right = Double.parseDouble(st.nextToken());
            double top = Double.parseDouble(st.nextToken());

            double width = right - left;
            double height = top - bottom;

            rects[i] = new Rectangle2D.Double(left, bottom, width, height);
        }

        return (int) getArea();
    }

    private double getSingleArea(Rectangle2D rect)
    {
        if (rect.getWidth() <= 0 || rect.getHeight() <= 0) {
            return 0;
        }
        return rect.getWidth() * rect.getHeight();
    }

    private double getArea()
    {
        if (rects.length == 1) {
            return getSingleArea(rects[0]);
        }

        if (rects.length == 2) {
            Rectangle2D ri = rects[0].createIntersection(rects[1]);
            return getSingleArea(rects[1]) + getSingleArea(rects[0])
                            - getSingleArea(ri);
        }

        if (rects.length == 3) {
            Rectangle2D r0 = rects[0].createIntersection(rects[1]);
            Rectangle2D r1 = rects[0].createIntersection(rects[2]);
            Rectangle2D r2 = rects[2].createIntersection(rects[1]);
            Rectangle2D r3 = rects[2].createIntersection(rects[1])
                            .createIntersection(rects[0]);

            return getSingleArea(rects[2]) + getSingleArea(rects[1])
                            + getSingleArea(rects[0]) - getSingleArea(r0)
                            - getSingleArea(r1) - getSingleArea(r2)
                            + getSingleArea(r3);
        }

        return 0;
    }
}
