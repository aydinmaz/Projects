package it.finsoft.RoomReserve;


import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.web.ErrorMvcAutoConfiguration;


import it.finsoft.RoomReserve.model.Room;
import it.finsoft.RoomReserve.repository.RoomRepository;

@SpringBootApplication
@EnableAutoConfiguration(exclude=ErrorMvcAutoConfiguration.class)
public class RoomReserveApplication implements CommandLineRunner
{

	
	@Autowired// what does this do?makes connection with database
    private RoomRepository roomrepos;//this is instansiating the interface and x is like a new object of this interface 
	
	
	
	public static void main(String[] args) 
	{  SpringApplication.run(RoomReserveApplication.class, args);  }
	
	@Override//what does this do?
	//@Transactional 
	public void run(String... arg0) throws Exception 
	{    List<Room> rooms=roomrepos.findAll();
		 if (rooms.isEmpty()) 
		 {  //List<Room> rooms = new ArrayList<>();
			String names[]={"Room A","Room B","Room C"};
			for(String elem:names)
			{
			    String days[]={"Monday","Tuseday","Wednesday","Thursday","Friday"};
		        for(String element:days)
			    {	for(int i=0; i<5;i++)
					    {  Room  r = new Room(elem,element, i+1 , false) ;
					    	rooms.add(r);  } 
			    }
		    }
	           roomrepos.save(rooms);//saves in mysql  
         }
		 
	}
	

	
	
	
	
}