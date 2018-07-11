import java.awt.Color;
import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
/*from w w w . j a  v a2  s. c  o m*/
import javax.imageio.ImageIO;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class Main {

    public static void main( final String[] args ) {
        int [] data = getArray();
        BufferedImage img = map( 320, 240 ,data);
        savePNG( img, "./test.bmp" );
    }

    public static int [] getArray(){
        String csvFile = "data.csv";
        BufferedReader br = null;
        String line = "";
        String cvsSplitBy = " ";

        try {

            br = new BufferedReader(new FileReader(csvFile));
            while ((line = br.readLine()) != null) {

                // use comma as separator
                String[] element = line.split(cvsSplitBy);
                int [] out = new int [element.length];
                for(int i=0;i<element.length;i++){
                    out[i] = Integer.parseInt(element[i], 16 );
                    //System.out.print(out[i]);
                    //System.out.print(" ");
                }

                return out;

            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    private static BufferedImage map( int sizeX, int sizeY ,int [] data){
        final BufferedImage res = new BufferedImage( sizeX, sizeY, BufferedImage.TYPE_INT_RGB );
        int i=0;
        for (int x = 0; x < sizeX; x++){
            for (int y = 0; y < sizeY; y++){
                res.setRGB(x, y, data[i]);
                i++;
            }
        }
        return res;
    }

    private static void savePNG( final BufferedImage bi, final String path ){
        try {
            RenderedImage rendImage = bi;
            ImageIO.write(rendImage, "bmp", new File(path));
            //ImageIO.write(rendImage, "PNG", new File(path));
            //ImageIO.write(rendImage, "jpeg", new File(path));
        } catch ( IOException e) {
            e.printStackTrace();
        }
    }

}