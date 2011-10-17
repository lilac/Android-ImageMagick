package magick;

public interface GeometryFlags {

    public static final int NoValue = 0x0000;
    public static final int PsiValue = 0x0001;
    public static final int XValue = 0x0001;
    public static final int XiValue = 0x0002;
    public static final int YValue = 0x0002;
    public static final int RhoValue = 0x0004;
    public static final int WidthValue = 0x0004;
    public static final int SigmaValue = 0x0008;
    public static final int HeightValue = 0x0008;
    public static final int ChiValue = 0x0010;
    public static final int XiNegative = 0x0020;
    public static final int XNegative = 0x0020;
    public static final int PsiNegative = 0x0040;
    public static final int YNegative = 0x0040;
    public static final int ChiNegative = 0x0080;
    public static final int PercentValue = 0x1000;
    public static final int AspectValue = 0x2000;
    public static final int LessValue = 0x4000;
    public static final int GreaterValue = 0x8000;
    public static final int MinimumValue = 0x10000;
    public static final int AreaValue = 0x20000;
    public static final int DecimalValue = 0x40000;
    public static final int AllValues = 0x7fffffff;

}
