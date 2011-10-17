package magick;



public class PixelPacket extends Magick {

    private int red, green, blue, opacity;

    // Constructor
    public PixelPacket(int red, int green, int blue, int opacity)
    {
	this.red = red;
	this.green = green;
	this.blue = blue;
	this.opacity = opacity;
    }

    // Set methods.
    public void setRed(int red)
    {
	this.red = red;
    }

    public void setGreen(int green)
    {
	this.green = green;
    }

    public void setBlue(int blue)
    {
	this.blue = blue;
    }

    public void setOpacity(int opacity)
    {
	this.opacity = opacity;
    }


    // Get Methods
    public int getRed()
    {
	return red;
    }

    public int getGreen()
    {
	return green;
    }

    public int getBlue()
    {
	return blue;
    }

    public int getOpacity()
    {
	return opacity;
    }

    /**
     * looks up a RGB values for a color given in the target string.
     *
     * @param target Specifies the color to lookup in the X color database
     * @return a PixelPacket that represents the target
     */
    public static native PixelPacket queryColorDatabase(String target)
	throws MagickException;
    

    /**
     * Display the object as a String
     * @see java.lang.Object#toString()
     */
    public String toString() {
        return "PixelPacket("+getRed()+","+getBlue()+","+getGreen()+","+getOpacity()+")";
    }
}
