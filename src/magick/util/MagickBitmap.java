package magick.util;

import java.awt.Dimension;
import java.nio.ByteBuffer;

import magick.MagickException;
import magick.MagickImage;
import android.graphics.Bitmap;
public class MagickBitmap {

	public static Bitmap ToBitmap(MagickImage img) throws MagickException {
		int width = img.getWidth();
		int height = img.getHeight();
		int count = width * height * 4;
		byte pixels[] = new byte[count];
		
		boolean res = img.dispatchImage(0, 0, width, height, "ARGB", pixels);
		//int colors[] = bytesToInts(pixels);
		int colors[] = toIntArray(pixels);
		if (res) {
			return Bitmap.createBitmap(colors, width, height, Bitmap.Config.ARGB_8888);
		}
		else return null;
	}
	public static int[] toIntArray(byte[] barr) { 
        //Pad the size to multiple of 4 
        int size = (barr.length / 4) + ((barr.length % 4 == 0) ? 0 : 1);      

        ByteBuffer bb = ByteBuffer.allocate(size *4); 
        bb.put(barr); 

        //Java uses Big Endian. Network program uses Little Endian. 
        //bb.order(ByteOrder.LITTLE_ENDIAN); 
       

        int[] result = new int[size]; 
        bb.rewind(); 
        while (bb.remaining() > 0) { 
            result[bb.position()/4] =bb.getInt(); 
        } 

        return result; 
	}
	
	public native static int[] bytesToInts(byte[] bytes);
	
	static {
		System.loadLibrary("android-magick");
	}
}
