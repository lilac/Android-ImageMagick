package magick;

/**
 * Corresponds to the ImageMagick enumerated type of the same name.
 *
 * @author Eric Yeo
 */
public interface PrimitiveType {

    public final static int UndefinedPrimitive = 0;
    public final static int PointPrimitive = 1;
    public final static int LinePrimitive = 2;
    public final static int RectanglePrimitive = 3;
    public final static int RoundRectanglePrimitive = 4;
    public final static int ArcPrimitive = 5;
    public final static int EllipsePrimitive = 6;
    public final static int CirclePrimitive = 7;
    public final static int PolylinePrimitive = 8;
    public final static int PolygonPrimitive = 9;
    public final static int BezierPrimitive = 10;
    public final static int ColorPrimitive = 11;
    public final static int MattePrimitive = 12;
    public final static int TextPrimitive = 13;
    public final static int ImagePrimitive = 14;
    public final static int PathPrimitive = 15;

}
