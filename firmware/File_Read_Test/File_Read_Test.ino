import java.io.FileReader;
//import java.io.FileNotFoundException;

ArrayList sensorData;
ArrayList columnOne;

void setup(){
  Data=new ArrayList();
  columnOne=new ArrayList();
  readData("C:\Users\Anthony Courville\Documents\GitHub\stewart-platform\firmware\servo_angles.csv");
}

void readData(String myFileName){
  
  File file=new File(myFileName);
  BufferedReader br=null;
  
  try{
    br=new BufferedReader(new FileReader(file));
    String text=null;
    
    while((text=br.readLine())!=null){
      String [] subtext = splitTokens(text,",");
      //columnOne.add(int(subtext[0]));
      Data.add(text);
    }
  }catch(FileNotFoundException e){
    e.printStackTrace();
  }catch(IOException e){
    e.printStackTrace();
  }finally{
    try {
      if (br != null){
        br.close();
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
  for (int i=0; i<sensorData.size()-1; i++){
    //print(columnOne.get(i) + ".....");
    println(sensorData.get(i));
  }
}
