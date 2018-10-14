import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Arc2D;

/**
 * @author: Bart Kiers
 */
public class GUI
    extends JFrame
{

    private GUI()
    {
        super("Circle Intersection Demo");
        initGUI();
    }

    private void initGUI()
    {
        super.setSize(600, 640);
        super.setDefaultCloseOperation(EXIT_ON_CLOSE);
        super.setLayout(new BorderLayout(5, 5));

        final Grid grid = new Grid();

        grid.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e)
            {
                Point p = new Point(e.getX(), e.getY()).toCartesianPoint(
                    grid.getWidth(), grid.getHeight());
                grid.showDraggedCircle(p);
            }
        });

        grid.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseReleased(MouseEvent e)
            {
                Point p = new Point(e.getX(), e.getY()).toCartesianPoint(
                    grid.getWidth(), grid.getHeight());
                grid.released(p);
            }

            @Override
            public void mousePressed(MouseEvent e)
            {
                Point p = new Point(e.getX(), e.getY()).toCartesianPoint(
                    grid.getWidth(), grid.getHeight());
                grid.pressed(p);
            }
        });

        super.add(grid, BorderLayout.CENTER);
        super.setVisible(true);
    }

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run()
            {
                new GUI();
            }
        });
    }

    private static class Grid
        extends JPanel
    {

        private Circle c1 = null;
        private Circle c2 = null;
        private Point screenClick = null;
        private Point currentPosition = null;

        public void released(Point p)
        {
            if (c1 == null || c2 != null) {
                c1 = new Circle(screenClick, screenClick.distance(p));
                c2 = null;
            } else {
                c2 = new Circle(screenClick, screenClick.distance(p));
            }
            screenClick = null;
            repaint();
        }

        public void pressed(Point p)
        {
            if (c1 != null && c2 != null) {
                c1 = null;
                c2 = null;
            }
            screenClick = p;
            repaint();
        }

        @Override
        public void paintComponent(Graphics g)
        {

            Graphics2D g2d = (Graphics2D) g;
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

            g2d.setColor(Color.WHITE);
            g2d.fillRect(0, 0, super.getWidth(), super.getHeight());

            final int W = super.getWidth();
            final int H = super.getHeight();
            g2d.setColor(Color.LIGHT_GRAY);
            g2d.drawLine(0, H / 2, W, H / 2); // x-axis
            g2d.drawLine(W / 2, 0, W / 2, H); // y-axis

            if (c1 != null) {
                g2d.setColor(Color.RED);
                c1.drawOn(g2d, W, H);
            }

            if (c2 != null) {
                g2d.setColor(Color.ORANGE);
                c2.drawOn(g2d, W, H);
            }

            if (screenClick != null && currentPosition != null) {
                g2d.setColor(Color.DARK_GRAY);
                g2d.setComposite(AlphaComposite.getInstance(
                    AlphaComposite.SRC_OVER, 0.5f));
                Circle temp = new Circle(screenClick,
                                screenClick.distance(currentPosition));
                temp.drawOn(g2d, W, H);
                currentPosition = null;
            }

            if (c1 != null && c2 != null) {

                g2d.setColor(Color.BLUE);
                g2d.setComposite(AlphaComposite.getInstance(
                    AlphaComposite.SRC_OVER, 0.4f));
                Point[] ips = c1.intersections(c2);
                for (Point ip : ips) {
                    ip.drawOn(g, W, H);
                }
                g2d.setComposite(AlphaComposite.getInstance(
                    AlphaComposite.SRC_OVER, 0.2f));
                if (ips.length == 2) {
                    g2d.setStroke(new BasicStroke(10.0f));
                    c1.highlightArc(g2d, ips[0], ips[1], W, H);
                }
            }

            g2d.dispose();
        }

        public void showDraggedCircle(Point p)
        {
            currentPosition = p;
            repaint();
        }
    }

    private static class Circle
    {

        public final Point center;
        public final double radius;

        public Circle(Point center, double radius)
        {
            this.center = center;
            this.radius = radius;
        }

        public void drawOn(Graphics g, int width, int height)
        {
            // translate Cartesian(x,y) to Screen(x,y)
            Point screenP = center.toScreenPoint(width, height);
            int r = (int) Math.rint(radius);
            g.drawOval((int) screenP.x - r, (int) screenP.y - r, r + r, r + r);

            // draw the center
            Point screenCenter = center.toScreenPoint(width, height);
            r = 4;
            g.drawOval((int) screenCenter.x - r, (int) screenCenter.y - r, r
                            + r, r + r);
        }

        public void highlightArc(
            Graphics2D g2d,
            Point p1,
            Point p2,
            int width,
            int height)
        {

            double a = center.degrees(p1);
            double b = center.degrees(p2);

            // translate Cartesian(x,y) to Screen(x,y)
            Point screenP = center.toScreenPoint(width, height);
            int r = (int) Math.rint(radius);

            // find the point to start drawing our arc
            double start = Math.abs(a - b) < 180 ? Math.min(a, b) : Math.max(a,
                b);

            // find the minimum angle to go from `start`-angle to the other
            // angle
            double extent = Math.abs(a - b) < 180 ? Math.abs(a - b)
                            : 360 - Math.abs(a - b);

            // draw the arc
            g2d.draw(new Arc2D.Double((int) screenP.x - r, (int) screenP.y - r,
                            r + r, r + r, start, extent, Arc2D.OPEN));
        }

        public Point[] intersections(Circle that)
        {

            // see: http://mathworld.wolfram.com/Circle-CircleIntersection.html
            double d = this.center.distance(that.center);
            double d1 = ((this.radius * this.radius)
                            - (that.radius * that.radius) + (d * d))
                            / (2 * d);
            double h = Math.sqrt((this.radius * this.radius) - (d1 * d1));
            double x3 = this.center.x + (d1 * (that.center.x - this.center.x))
                            / d;
            double y3 = this.center.y + (d1 * (that.center.y - this.center.y))
                            / d;
            double x4_i = x3 + (h * (that.center.y - this.center.y)) / d;
            double y4_i = y3 - (h * (that.center.x - this.center.x)) / d;
            double x4_ii = x3 - (h * (that.center.y - this.center.y)) / d;
            double y4_ii = y3 + (h * (that.center.x - this.center.x)) / d;

            if (Double.isNaN(x4_i)) {
                // no intersections
                return new Point[0];
            }

            // create the intersection points
            Point i1 = new Point(x4_i, y4_i);
            Point i2 = new Point(x4_ii, y4_ii);

            if (i1.distance(i2) < 0.0000000001) {
                // i1 and i2 are (more or less) the same: a single intersection
                return new Point[] { i1 };
            }

            // two unique intersections
            return new Point[] { i1, i2 };
        }

        @Override
        public String toString()
        {
            return String.format("{center=%s, radius=%.2f}", center, radius);
        }
    }

    private static class Point
    {

        public final double x;
        public final double y;

        public Point(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        public double degrees(Point that)
        {
            double deg = Math.toDegrees(Math.atan2(that.y - this.y, that.x
                            - this.x));
            return deg < 0.0 ? deg + 360 : deg;
        }

        public double distance(Point that)
        {
            double dX = this.x - that.x;
            double dY = this.y - that.y;
            return Math.sqrt(dX * dX + dY * dY);
        }

        public void drawOn(Graphics g, int width, int height)
        {
            // translate Cartesian(x,y) to Screen(x,y)
            Point screenP = toScreenPoint(width, height);
            int r = 7;
            g.fillOval((int) screenP.x - r, (int) screenP.y - r, r + r, r + r);
        }

        public Point toCartesianPoint(int width, int height)
        {
            double xCart = x - (width / 2);
            double yCart = -(y - (height / 2));
            return new Point(xCart, yCart);
        }

        public Point toScreenPoint(int width, int height)
        {
            double screenX = x + (width / 2);
            double screenY = -(y - (height / 2));
            return new Point(screenX, screenY);
        }

        @Override
        public String toString()
        {
            return String.format("(%.2f,%.2f)", x, y);
        }
    }
}
