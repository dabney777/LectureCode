package com.test;

import java.io.IOException;
import java.io.ObjectInput;

/**
 * Created by Dabney on 10/25/2016.
 */

public class Test {


    public static void main(String []args ){
        try{
            Test a= new Test();
            //a.aWrong();
            Person tmp = new Person();
            Class<?> tmp1 =Class.forName("com.test.Person");

            Class<?> tmp2=Person.class;

            Object tmpx = tmp2.newInstance();
            Class<?> tmp3=new Person().getClass();
            Class<Person> tmp4 = Person.class;
            Class<?> tmp5  = Object.class;
            Class<?> tmp6  = new Object().getClass();
            Class<?> tmp7  = new Object().getClass();
            System.out.println("tmp: "+tmp.getClass().getName()+"\ntmp1: "+tmp1.getName()+"\ntmp2: "+tmp2.getName()+"\n"+"tmp3:"+tmp3.getName());
            System.out.println("tmp4: "+Class.class.getName());
            System.out.println("tmpx:"+tmpx.getClass().getName());
            Object ss = Object.class.newInstance();
            System.out.println("Object:"+ss==new Object());
        }catch (Exception e){
            System.out.println(e.getMessage());
            System.exit(0);
        }



        System.out.println("On the way\n");

    }
    public int aWrong() throws Exception{
        throw new IndexOutOfBoundsException("aWrong");

    }

}
