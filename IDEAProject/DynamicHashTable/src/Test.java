import java.io.IOException;

/**
 * Created by Dabney on 10/25/2016.
 */
public class Test {
    public static void main(String []args ){
        try{
            Test a= new Test();
            a.aWrong();

        }catch (Exception e){
            System.out.println(e.getMessage());
            System.exit();
        }
        System.out.println("On the way");

    }
    public int aWrong() throws Exception{
        throw new IndexOutOfBoundsException("aWrong");

    }

}
