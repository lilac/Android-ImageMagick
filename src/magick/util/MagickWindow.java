package magick.util;

import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import magick.MagickImage;


/**
 * This class implements a window that displays a MagickImage.
 *
 * @author Eric Yeo
 */
public class MagickWindow extends Frame {

    /**
     * A listener that exits the application when we receive
     * the window closing event.
     */
    private final class MyListener extends WindowAdapter {

	/**
	 * This method is called when the window closes.
	 */
	public void windowClosing(WindowEvent event)
	{
	    System.exit(0);
	}
    }

    /**
     * We want the window size to be this big.
     */
    public Dimension getPreferredSize() {
	return new Dimension(250, 200);
    }

    /**
     * We want the window size to be at this minimum.
     */
    public Dimension getMinimumSize() {
	return new Dimension(300, 200);
    }


    /**
     * Constructor.
     */
    public MagickWindow(MagickImage image)
    {
	setResizable(true);
	addWindowListener(new MyListener());

	MagickViewer imageViewer = new MagickViewer();
	add(imageViewer, "Center");

	setTitle("Magick Window");
	pack();
	imageViewer.setImage(image);
    }

}
