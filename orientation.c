#include "stdio.h"   
#include "stdlib.h"
#include "udf.h"
#include "math.h"
#include "mem.h"
#include "sg.h"

DEFINE_ON_DEMAND(orientation)
{
	Domain *domain=Get_Domain(1);
	Thread *t;
	cell_t c;
	int i;

	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
#if RP_2D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;
			C_UDMI(c,t,6)=0.0;
			C_UDMI(c,t,7)=0.0;
			C_UDMI(c,t,8)=0.0;
#endif
		}
		end_c_loop(c,t)
	}

	Random(); 
	
	//Initial_condition();
	
	for (i=0;i<20;i++) 
	{
//		

		thread_loop_c(t,domain)
		{
			begin_c_loop(c,t)
			{
#if RP_2D
				C_UDMI(c,t,3)=0.0;
				C_UDMI(c,t,4)=0.0;
				C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
				C_UDMI(c,t,5)=0.0;
				C_UDMI(c,t,6)=0.0;
				C_UDMI(c,t,7)=0.0;
				C_UDMI(c,t,8)=0.0;
#endif
			}
			end_c_loop(c,t)
		}

		Evolution();
		//		Message("Evolution Equation: %i is done.\n", i);
		thread_loop_c(t,domain) 
		{
		begin_c_loop(c,t)
		{
		#if RP_2D
		C_UDMI(c,t,1)+=C_UDMI(c,t,3);
		C_UDMI(c,t,2)+=C_UDMI(c,t,4);
		if ((C_UDMI(c,t,1)>0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		if ((C_UDMI(c,t,1)<0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}

		C_UDMI(c,t,1)=C_UDMI(c,t,1)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));

		#endif
		#if RP_3D

		C_UDMI(c,t,2)+=C_UDMI(c,t,5);
		C_UDMI(c,t,3)+=C_UDMI(c,t,6);
		C_UDMI(c,t,4)+=C_UDMI(c,t,7);
		/*This part applys the fact that directors have sence but not direction*/
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}

		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,3)=C_UDMI(c,t,3)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,4)=C_UDMI(c,t,4)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));

		#endif
		}
		end_c_loop(c,t)
		}
	}
	OrderParameter();
	
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
#if RP_2D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;
			C_UDMI(c,t,6)=0.0;
			C_UDMI(c,t,7)=0.0;
			C_UDMI(c,t,8)=0.0;
#endif
		}
		end_c_loop(c,t)
	}

	Random(); 
	
	for (i=0;i<20;i++) 
	{
//		Message("Itteration: %i is done.\n", i);

		thread_loop_c(t,domain)
		{
			begin_c_loop(c,t)
			{
#if RP_2D
				C_UDMI(c,t,3)=0.0;
				C_UDMI(c,t,4)=0.0;
				C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
				C_UDMI(c,t,5)=0.0;
				C_UDMI(c,t,6)=0.0;
				C_UDMI(c,t,7)=0.0;
				C_UDMI(c,t,8)=0.0;
#endif
			}
			end_c_loop(c,t)
		}


		Frank(); 
		//		Message("Franks Equation: %i is done.\n", i);
		
		thread_loop_c(t,domain)
		{
		begin_c_loop(c,t)
		{
		#if RP_2D
		C_UDMI(c,t,1)+=C_UDMI(c,t,3);
		C_UDMI(c,t,2)+=C_UDMI(c,t,4);
		
		if ((C_UDMI(c,t,1)>0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		if ((C_UDMI(c,t,1)<0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		
		C_UDMI(c,t,1)=C_UDMI(c,t,1)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		#endif

		#if RP_3D

		C_UDMI(c,t,2)+=C_UDMI(c,t,5);
		C_UDMI(c,t,3)+=C_UDMI(c,t,6);
		C_UDMI(c,t,4)+=C_UDMI(c,t,7);

		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,3)=C_UDMI(c,t,3)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,4)=C_UDMI(c,t,4)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));

		#endif
		}
		end_c_loop(c,t)
		}

	}
	OrderParameter();

thread_loop_c(t,domain) 
	{
		begin_c_loop(c,t)
		{
#if RP_2D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
			C_UDMI(c,t,0)=0.0;
			C_UDMI(c,t,1)=0.0;
			C_UDMI(c,t,2)=0.0;
			C_UDMI(c,t,3)=0.0;
			C_UDMI(c,t,4)=0.0;
			C_UDMI(c,t,5)=0.0;
			C_UDMI(c,t,6)=0.0;
			C_UDMI(c,t,7)=0.0;
			C_UDMI(c,t,8)=0.0;
#endif
		}
		end_c_loop(c,t)
	}

	Random();  
	
	for (i=0;i<20;i++)  
	{
	//	Message("Itteration: %i is done.\n", i);

		thread_loop_c(t,domain) 
		{
			begin_c_loop(c,t)
			{
#if RP_2D
				C_UDMI(c,t,3)=0.0;
				C_UDMI(c,t,4)=0.0;
				C_UDMI(c,t,5)=0.0;

#endif
#if RP_3D
				C_UDMI(c,t,5)=0.0;
				C_UDMI(c,t,6)=0.0;
				C_UDMI(c,t,7)=0.0;
				C_UDMI(c,t,8)=0.0;
#endif
			}
			end_c_loop(c,t)
		}

		Evolution(); 
		thread_loop_c(t,domain) 
		{
		begin_c_loop(c,t)
		{
		#if RP_2D
		C_UDMI(c,t,1)+=C_UDMI(c,t,3);
		C_UDMI(c,t,2)+=C_UDMI(c,t,4);
		if ((C_UDMI(c,t,1)>0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		if ((C_UDMI(c,t,1)<0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}

		C_UDMI(c,t,1)=C_UDMI(c,t,1)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));

		#endif
		#if RP_3D

		C_UDMI(c,t,2)+=C_UDMI(c,t,5);
		C_UDMI(c,t,3)+=C_UDMI(c,t,6);
		C_UDMI(c,t,4)+=C_UDMI(c,t,7);
		 
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}

		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,3)=C_UDMI(c,t,3)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,4)=C_UDMI(c,t,4)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));

		#endif
		}
		end_c_loop(c,t)
		}

		thread_loop_c(t,domain) 
		{
		begin_c_loop(c,t)
		{
		#if RP_2D
		C_UDMI(c,t,3)=0.0;
		C_UDMI(c,t,4)=0.0;
		C_UDMI(c,t,5)=0.0;

		#endif
		#if RP_3D
		C_UDMI(c,t,5)=0.0;
		C_UDMI(c,t,6)=0.0;
		C_UDMI(c,t,7)=0.0;
		C_UDMI(c,t,8)=0.0;
		#endif
		}
		end_c_loop(c,t)
		}

		Frank();  
		
		thread_loop_c(t,domain)
		{
		begin_c_loop(c,t)
		{
		#if RP_2D
		C_UDMI(c,t,1)+=C_UDMI(c,t,3);
		C_UDMI(c,t,2)+=C_UDMI(c,t,4);
		
		if ((C_UDMI(c,t,1)>0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		if ((C_UDMI(c,t,1)<0) && (C_UDMI(c,t,2)<0))
		{
		C_UDMI(c,t,1)*=-1.0;
		C_UDMI(c,t,2)*=-1.0;
		}
		
		C_UDMI(c,t,1)=C_UDMI(c,t,1)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,1),2)+pow(C_UDMI(c,t,2),2));
		#endif

		#if RP_3D

		C_UDMI(c,t,2)+=C_UDMI(c,t,5);
		C_UDMI(c,t,3)+=C_UDMI(c,t,6);
		C_UDMI(c,t,4)+=C_UDMI(c,t,7);

		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
		{
		C_UDMI(c,t,2)*=-1.0;
		C_UDMI(c,t,3)*=-1.0;
		C_UDMI(c,t,4)*=-1.0;
		}
		
		C_UDMI(c,t,2)=C_UDMI(c,t,2)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,3)=C_UDMI(c,t,3)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
		C_UDMI(c,t,4)=C_UDMI(c,t,4)/sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));

		#endif
		}
		end_c_loop(c,t)
		}

		Translation();
		thread_loop_c(t,domain)
		{
			begin_c_loop(c,t)
			{
				
#if RP_2D
				if(C_UDMI(c,t,5)>0)
				{
					 
					C_UDMI(c,t,1)=C_UDMI(c,t,3)/sqrt(pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
					C_UDMI(c,t,2)=C_UDMI(c,t,4)/sqrt(pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2));
					if ((C_UDMI(c,t,1)>0) && (C_UDMI(c,t,2)<0))
					{
						C_UDMI(c,t,1)*=-1.0;
						C_UDMI(c,t,2)*=-1.0;
					}
					if ((C_UDMI(c,t,1)<0) && (C_UDMI(c,t,2)<0))
					{
						C_UDMI(c,t,1)*=-1.0;
						C_UDMI(c,t,2)*=-1.0;
					}
				}
				else if(C_UDMI(c,t,5)==0)
				{/*This happens on the boundaries of the flow domain*/

					C_UDMI(c,t,0)=(rand()%31416)/10000.0;
					C_UDMI(c,t,1)=cos(C_UDMI(c,t,0));/*x component of the director*/
					C_UDMI(c,t,2)=sin(C_UDMI(c,t,0));/*y component of the director*/
				}
#endif

#if RP_3D
				if(C_UDMI(c,t,8)>0)
				{
				 
					C_UDMI(c,t,2)=C_UDMI(c,t,5)/sqrt(pow(C_UDMI(c,t,5),2)+pow(C_UDMI(c,t,6),2)+pow(C_UDMI(c,t,7),2));
					C_UDMI(c,t,3)=C_UDMI(c,t,6)/sqrt(pow(C_UDMI(c,t,5),2)+pow(C_UDMI(c,t,6),2)+pow(C_UDMI(c,t,7),2));
					C_UDMI(c,t,4)=C_UDMI(c,t,7)/sqrt(pow(C_UDMI(c,t,5),2)+pow(C_UDMI(c,t,6),2)+pow(C_UDMI(c,t,7),2));
					if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
					{
						C_UDMI(c,t,2)*=-1.0;
						C_UDMI(c,t,3)*=-1.0;
						C_UDMI(c,t,4)*=-1.0;
					}
					if ((C_UDMI(c,t,2)>0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
					{
						C_UDMI(c,t,2)*=-1.0;
						C_UDMI(c,t,3)*=-1.0;
						C_UDMI(c,t,4)*=-1.0;
					}
					if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)>0))
					{
						C_UDMI(c,t,2)*=-1.0;
						C_UDMI(c,t,3)*=-1.0;
						C_UDMI(c,t,4)*=-1.0;
					}
					if ((C_UDMI(c,t,2)<0) && (C_UDMI(c,t,3)<0) && (C_UDMI(c,t,4)<0))
					{
						C_UDMI(c,t,2)*=-1.0;
						C_UDMI(c,t,3)*=-1.0;
						C_UDMI(c,t,4)*=-1.0;
					}
				}
				else if(C_UDMI(c,t,8)==0)
				{
					C_UDMI(c,t,0)=(rand()%31416)/10000.0;
					C_UDMI(c,t,1)=(rand()%31416)/10000.0;
					C_UDMI(c,t,2)=sin(C_UDMI(c,t,1))*cos(C_UDMI(c,t,0));/*x component of the director*/
					C_UDMI(c,t,3)=sin(C_UDMI(c,t,1))*sin(C_UDMI(c,t,0));/*y component of the director*/
					C_UDMI(c,t,4)=cos(C_UDMI(c,t,1));/*z component of the director*/
				}															
#endif 
				
				
			}
			end_c_loop(c,t)
		}
	}
	OrderParameter();

Message("Done.\n");
}

void Random()
{
	Domain *domain=Get_Domain(1);
	Thread *t;
	cell_t c;
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			C_UDMI(c,t,0)=(rand()%31416)/10000.0;

#if RP_2D
			Set_User_Memory_Name(0,"angle_from_x_axis");
			Set_User_Memory_Name(1,"directors_x_component");
			Set_User_Memory_Name(2,"directors_y_component");
			C_UDMI(c,t,1)=cos(C_UDMI(c,t,0));/*x component of the director*/
			C_UDMI(c,t,2)=sin(C_UDMI(c,t,0));/*y component of the director*/
#endif

#if RP_3D
			C_UDMI(c,t,1)=(rand()%31416)/10000.0;
			Set_User_Memory_Name(0,"angle_from_x_axis");
			Set_User_Memory_Name(1,"angle_from_y_axis");
			Set_User_Memory_Name(2,"directors_x_component");
			Set_User_Memory_Name(3,"directors_y_component");
			Set_User_Memory_Name(4,"directors_z_component");
			C_UDMI(c,t,2)=sin(C_UDMI(c,t,1))*cos(C_UDMI(c,t,0));/*x component of the director*/
			C_UDMI(c,t,3)=sin(C_UDMI(c,t,1))*sin(C_UDMI(c,t,0));/*y component of the director*/
			C_UDMI(c,t,4)=cos(C_UDMI(c,t,1));/*z component of the director*/
#endif

		}
		end_c_loop(c,t) 
	}                   
}

void Evolution()
{
	 
	Domain *domain=Get_Domain(1);
	Thread *t;
	cell_t c;
	face_t f;
	double Deltat=1.e-4,Lambda=1.05,nx,ny,nz,AA1,AA2,AA3,max=-10.0,min=-10.0;
	double A[ND_ND][ND_ND],W[ND_ND][ND_ND],DeltaNW[ND_ND],DeltaNA[ND_ND];
	int i;
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			A[0][0]=(-1.0)*C_DUDX(c,t);
			A[0][1]=0.5*(C_DUDY(c,t)+C_DVDX(c,t));
			A[1][0]=A[0][1];
			A[1][1]=(-1.0)*C_DVDY(c,t);
			W[0][0]=0.0;
			W[0][1]=0.5*(C_DUDY(c,t)-C_DVDX(c,t));
			W[1][0]=(-1.0)*W[0][1]; /*0.5*(C_DVDX(c,t)-C_DUDY(c,t));*/
			W[1][1]=0.0;
#if RP_2D
			nx=C_UDMI(c,t,1);
			ny=C_UDMI(c,t,2);
#endif

#if RP_3D
			A[0][2]=0.5*(C_DUDZ(c,t)+C_DWDX(c,t));
			A[1][2]=0.5*(C_DVDZ(c,t)+C_DWDY(c,t));
			A[2][2]=C_DWDZ(c,t);
			A[2][1]=A[1][2];
			A[2][0]=A[0][2];
			W[0][2]=0.5*(C_DUDZ(c,t)-C_DWDX(c,t));
			W[1][2]=0.5*(C_DVDZ(c,t)-C_DWDY(c,t));
			W[2][2]=0.0;
			W[2][1]=(-1.0)*W[1][2]; /*0.5*(C_DWDY(c,t)-C_DVDZ(c,t));*/
			W[2][0]=(-1.0)*W[0][2]; /*0.5*(C_DWDX(c,t)-C_DUDZ(c,t));*/
			nx=C_UDMI(c,t,2);
			ny=C_UDMI(c,t,3);
			nz=C_UDMI(c,t,4);
#endif

			DeltaNW[0]=Deltat*(nx*W[0][0]+ny*W[0][1]);
			DeltaNW[1]=Deltat*(nx*W[1][0]+ny*W[1][1]);

#if RP_3D
			DeltaNW[0]+=Deltat*(nz*W[0][2]);
			DeltaNW[1]+=Deltat*(nz*W[1][2]);   
			DeltaNW[2]=Deltat*(nx*W[2][0]+ny*W[2][1]+nz*W[2][2]);
#endif

#if RP_2D
			DeltaNA[0]=(nx*A[0][0]+ny*A[1][0]-(nx*(nx*A[0][0]+ny*A[1][0])+ny*(nx*A[0][1]+ny*A[1][1]))*nx)*Deltat;
			DeltaNA[1]=(nx*A[0][1]+ny*A[1][1]-(nx*(nx*A[0][0]+ny*A[1][0])+ny*(nx*A[0][1]+ny*A[1][1]))*ny)*Deltat;
#endif

#if RP_3D
			DeltaNA[0]=(nx*A[0][0]+ny*A[1][0]+nz*A[2][0]-(nx*(nx*A[0][0]+ny*A[1][0]+nz*A[2][0])+ny*(nx*A[0][1]+ny*A[1][1]+nz*A[2][1])+nz*(nx*A[0][2]+ny*A[1][2]+nz*A[2][2])))*Deltat;
			DeltaNA[1]=(nx*A[0][1]+ny*A[1][1]+nz*A[2][1]-(nx*(nx*A[0][0]+ny*A[1][0]+nz*A[2][0])+ny*(nx*A[0][1]+ny*A[1][1]+nz*A[2][1])+nz*(nx*A[0][2]+ny*A[1][2]+nz*A[2][2])))*Deltat;
			DeltaNA[2]=(nx*A[0][2]+ny*A[1][2]+nz*A[2][2]-(nx*(nx*A[0][0]+ny*A[1][0]+nz*A[2][0])+ny*(nx*A[0][1]+ny*A[1][1]+nz*A[2][1])+nz*(nx*A[0][2]+ny*A[1][2]+nz*A[2][2])))*Deltat;
#endif

#if RP_2D
			 
			C_UDMI(c,t,3)=DeltaNW[0]+Lambda*DeltaNA[0];
			C_UDMI(c,t,4)=DeltaNW[1]+Lambda*DeltaNA[1];

			if ((C_UDMI(c,t,3) > 2.0))
			{
				Message("C_UDMI(c,t,3)is: %e and C_UDMI(c,t,4) is: %e .\n", C_UDMI(c,t,3) ,C_UDMI(c,t,4));
			}
			
			if (C_UDMI(c,t,3) == 0.0)
			{
				Message("C_UDMI(c,t,3)= %e and C_UDMI(c,t,4)= %e .\n", C_UDMI(c,t,3) ,C_UDMI(c,t,4));
			}
			 

#endif

#if RP_3D
			 
			C_UDMI(c,t,5)=DeltaNW[0]+Lambda*DeltaNA[0];
			C_UDMI(c,t,6)=DeltaNW[1]+Lambda*DeltaNA[1];
			C_UDMI(c,t,7)=DeltaNW[2]+Lambda*DeltaNA[2];



			if (sqrt(pow(C_UDMI(c,t,2),2)+pow(C_UDMI(c,t,3),2)+pow(C_UDMI(c,t,4),2))>1.1)
			{
				Message("Deltat is too large and the magnitude of dn is larger than 0.1.\n");
				Message("New director's length for cell %i is: %f \n",c,sqrt(pow(C_UDMI(c,t,5),2)+pow(C_UDMI(c,t,6),2)+pow(C_UDMI(c,t,7),2)));
			}

#endif

		}
		end_c_loop(c,t)
	}
}

void Frank()
{
	/*FILE *pf;*/
	Domain *domain=Get_Domain(1);
	Thread *t;
	Thread *tf;
	cell_t c;
	cell_t cn,c_n;
	face_t f;
	int Neighbors;
	int n,i;
	double k=1e-2; /*Franks elastic constant*/
	double Energy=0.0,deltat=1e-4,Rotational_viscosity=10.0;
	double nx,ny,nz,nx_c,ny_c,nz_c,nx_i,ny_i,nz_i;
	double delta_mag,theta_i,deltan_x,deltan_y,deltan_z;
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			Neighbors=0;  
			deltan_x=0.0;
			deltan_y=0.0;
			deltan_z=0.0;
			c_face_loop(c,t,n) /*Loops over all the faces of a cell */
			{
				 
				f=C_FACE(c,t,n);  
				tf=C_FACE_THREAD(c,t,n);  
				if(!BOUNDARY_FACE_THREAD_P(tf))  
				{
					Neighbors++;
					if(F_C0(f,tf)==c)
					{
#if RP_2D
						/*the neighboring cell's index*/
						c_n=F_C1(f,tf);

						/* x and y components of the center cell's director */
						nx_c=C_UDMI(c,t,1);
						ny_c=C_UDMI(c,t,2);

						 
						nx_i=C_UDMI(c_n,t,1);
						ny_i=C_UDMI(c_n,t,2);

						 
						theta_i=acos((nx_i*nx_c+ny_i*ny_c)/(sqrt(pow(nx_i,2)+pow(ny_i,2))*sqrt(pow(nx_c,2)+pow(ny_c,2))+1e-10));

						 
						delta_mag=deltat*k*sin(theta_i)*cos(theta_i)/Rotational_viscosity;
						deltan_x+=delta_mag*(nx_i-nx_c);
						deltan_y+=delta_mag*(ny_i-ny_c);

						Energy+=k/2.0*pow(sin(theta_i),2);
						
						//						Message("Franks Energy is: %f \n", Energy);
#endif

#if RP_3D
						 
						c_n=F_C1(f,tf);

						 
						nx_c=C_UDMI(c,t,2);
						ny_c=C_UDMI(c,t,3);
						nz_c=C_UDMI(c,t,4);

						 
						nx_i=C_UDMI(c_n,t,2);
						ny_i=C_UDMI(c_n,t,3);
						nz_i=C_UDMI(c_n,t,4);

						
						theta_i=acos((nx_i*nx_c+ny_i*ny_c+nz_i*nz_c)/(sqrt(pow(nx_i,2)+pow(ny_i,2)+pow(nz_i,2))*sqrt(pow(nx_c,2)+pow(ny_c,2)+pow(nz_c,2))+1e-10));

						 delta_mag=deltat*k*sin(theta_i)*cos(theta_i)/Rotational_viscosity;
						deltan_x+=delta_mag*(nx_i-nx_c);
						deltan_y+=delta_mag*(ny_i-ny_c);
						deltan_z+=delta_mag*(nz_i-nz_c);      


						Energy+=k/2.0*pow(sin(theta_i),2);
#endif
					}
					else
					{
#if RP_2D
						 
						c_n=F_C0(f,tf);

						 
						nx_c=C_UDMI(c,t,1);
						ny_c=C_UDMI(c,t,2);

						 
						nx_i=C_UDMI(c_n,t,1);
						ny_i=C_UDMI(c_n,t,2);

						 
						theta_i=acos((nx_i*nx_c+ny_i*ny_c)/(sqrt(pow(nx_i,2)+pow(ny_i,2))*sqrt(pow(nx_c,2)+pow(ny_c,2))+1e-10));

						 
						delta_mag=deltat*k*sin(theta_i)*cos(theta_i)/Rotational_viscosity;
						deltan_x+=delta_mag*(nx_i-nx_c);
						deltan_y+=delta_mag*(ny_i-ny_c);

						Energy+=k/2.0*pow(sin(theta_i),2);
#endif

#if RP_3D
						 
						c_n=F_C0(f,tf);

						 
						nx_c=C_UDMI(c,t,2);
						ny_c=C_UDMI(c,t,3);
						nz_c=C_UDMI(c,t,4);

						 
						nx_i=C_UDMI(c_n,t,2);
						ny_i=C_UDMI(c_n,t,3);
						nz_i=C_UDMI(c_n,t,4);

						 
						theta_i=acos((nx_i*nx_c+ny_i*ny_c+nz_i*nz_c)/(sqrt(pow(nx_i,2)+pow(ny_i,2)+pow(nz_i,2))*sqrt(pow(nx_c,2)+pow(ny_c,2)+pow(nz_c,2))+1e-10));

						 
						delta_mag=deltat*k*sin(theta_i)*cos(theta_i)/Rotational_viscosity;
						deltan_x+=delta_mag*(nx_i-nx_c);
						deltan_y+=delta_mag*(ny_i-ny_c);
						deltan_z+=delta_mag*(nz_i-nz_c);      


						Energy+=k/2.0*pow(sin(theta_i),2);
#endif
					}
				}
			}

			 
#if RP_2D
			C_UDMI(c,t,3)+=deltan_x;
			C_UDMI(c,t,4)+=deltan_y;
#endif

#if RP_3D
			C_UDMI(c,t,5)+=deltan_x;
			C_UDMI(c,t,6)+=deltan_y;
			C_UDMI(c,t,7)+=deltan_z;
#endif

		}
		end_c_loop(c,t)
	}
 
}

void Translation()
{
	/*FILE *pf;*/
	Domain *domain=Get_Domain(1);
	Thread *t,*tf;
	cell_t c,cn,c_n;
	face_t f;
	int Neighbors,n,i; 
	double deltat=1e-4,A[ND_ND],ds,es[ND_ND],A_by_es,dr0[ND_ND],dr1[ND_ND],vel[ND_ND],Energy=0.0,dx,Angle,alpha;

	thread_loop_c(t,domain)  
	{
		begin_c_loop(c,t)
		{
#if RP_2D
			C_UDMI(c,t,3)=0.0; /*the effect of neighbors on nx of cell c*/
			C_UDMI(c,t,4)=0.0; /*the effect of neighbors on ny of cell c*/
			C_UDMI(c,t,5)=0.0; /*number of neighbors contributing to a cell c*/
			C_UDMI(c,t,6)=0.0;
#endif
#if RP_3D
			C_UDMI(c,t,5)=0.0; /*the effect of neighbors on nx of cell c*/
			C_UDMI(c,t,6)=0.0; /*the effect of neighbors on ny of cell c*/
			C_UDMI(c,t,7)=0.0; /*the effect of neighbors on nz of cell c*/
			C_UDMI(c,t,8)=0.0;/*number of neighbors contributing to a cell*/
#endif
		}
		end_c_loop(c,t)
	}

	thread_loop_c(t,domain)  
	{
		begin_c_loop(c,t)
		{
			Neighbors=0;  
			c_face_loop(c,t,n)  
			{
				 
				f=C_FACE(c,t,n);  
				tf=C_FACE_THREAD(c,t,n); 
				if(!BOUNDARY_FACE_THREAD_P(tf))  
				{
					Neighbors++;  

					INTERIOR_FACE_GEOMETRY(f,tf,A,ds,es,A_by_es,dr0,dr1);
					 

					ND_SET(vel[0],vel[1],vel[2],C_U(c,t),C_V(c,t),C_W(c,t));
					 
					if(F_C0(f,tf)==c)
					{ 

						Angle=acos(NV_DOT(A,vel)/(NV_MAG(A)*NV_MAG(vel)+1e-10));
						 

						dx=NV_MAG(vel)*cos(Angle)*deltat;
						 						
						
						if ((Angle<1.5))//&&(C_UDMI(c_n,t,5)<1.0))
						{
							C_UDMI(c,t,6)=dx/ds;

							c_n=F_C1(f,tf); /*the neighboring cell's index*/
							
#if RP_2D
							C_UDMI(c_n,t,5)+=1.0;
							if ((dx/ds)>=1.0)
							{
								C_UDMI(c_n,t,3)+=C_UDMI(c,t,1);
								C_UDMI(c_n,t,4)+=C_UDMI(c,t,2);
								
							}
							else 
							{
								C_UDMI(c_n,t,3)+=C_UDMI(c_n,t,1);
								C_UDMI(c_n,t,4)+=C_UDMI(c_n,t,2);
								// alpha=acos((C_UDMI(c,t,1)*C_UDMI(c_n,t,1)+C_UDMI(c,t,2)*C_UDMI(c_n,t,2))/sqrt(pow(C_UDMI(c,t,1),2)+
								// pow(C_UDMI(c,t,2),2))/sqrt(pow(C_UDMI(c_n,t,1),2)+pow(C_UDMI(c_n,t,2),2)));
								// if (alpha<1.571)
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*(C_UDMI(c,t,1)-C_UDMI(c_n,t,1))+C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*(C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								// }
								// else
								// {
								// if(C_UDMI(c,t,1)<0.0)
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*((-1.0)*C_UDMI(c,t,1)-C_UDMI(c_n,t,1))+C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*((-1.0)*C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								// }
								// else
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*(C_UDMI(c,t,1)+C_UDMI(c_n,t,1))-C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*(C_UDMI(c,t,2)+C_UDMI(c_n,t,2))-C_UDMI(c_n,t,2);
								// }
								// }
								

							}
							
							if ((dx/ds) > 2.5)
							{
								Message("dx/ds is: %e for cell %i. deltat should be reduced to reduce the dx for the given velocity.\n", dx/ds,c);
							}

#endif

#if RP_3D
							C_UDMI(c_n,t,8)+=1;
							if ((dx/ds)>=1.0)
							{
								C_UDMI(c_n,t,5)+=C_UDMI(c,t,2);
								C_UDMI(c_n,t,6)+=C_UDMI(c,t,3);
								C_UDMI(c_n,t,7)+=C_UDMI(c,t,4);

							}
							else
							{
								C_UDMI(c_n,t,5)+=C_UDMI(c_n,t,2); //(dx/ds)*(C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								C_UDMI(c_n,t,6)+=C_UDMI(c_n,t,3); //(dx/ds)*(C_UDMI(c,t,3)-C_UDMI(c_n,t,3))+C_UDMI(c_n,t,3);
								C_UDMI(c_n,t,7)+=C_UDMI(c_n,t,4); //(dx/ds)*(C_UDMI(c,t,4)-C_UDMI(c_n,t,4))+C_UDMI(c_n,t,4);

							}

#endif
						}
					}
					else
					{/*C1 is the center cell here*/

						// this is wrong!		A=(-1.0)*A; 
						for (i=0;i<ND_ND;++i)A[i]=(-1.0)*A[i];
						Angle=acos(NV_DOT(A,vel)/(NV_MAG(A)*NV_MAG(vel)+1e-10));
						 

						dx=NV_MAG(vel)*cos(Angle)*deltat;
						 
						
						if ((Angle<1.1))//&&(C_UDMI(c_n,t,5)<1.0))
						{
							
							C_UDMI(c,t,6)=dx/ds;
							
							/*the neighboring cell's index*/
							c_n=F_C0(f,tf);
#if RP_2D
							C_UDMI(c_n,t,5)+=1.0;
							if ((dx/ds)>=1.0)
							{
								C_UDMI(c_n,t,3)+=C_UDMI(c,t,1);
								C_UDMI(c_n,t,4)+=C_UDMI(c,t,2);
								
							}
							else 
							{
								C_UDMI(c_n,t,3)+=C_UDMI(c_n,t,1);
								C_UDMI(c_n,t,4)+=C_UDMI(c_n,t,2);
								// alpha=acos((C_UDMI(c,t,1)*C_UDMI(c_n,t,1)+C_UDMI(c,t,2)*C_UDMI(c_n,t,2))/sqrt(pow(C_UDMI(c,t,1),2)+
								// pow(C_UDMI(c,t,2),2))/sqrt(pow(C_UDMI(c_n,t,1),2)+pow(C_UDMI(c_n,t,2),2)));
								// if (alpha<1.571)
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*(C_UDMI(c,t,1)-C_UDMI(c_n,t,1))+C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*(C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								// }
								// else
								// {
								// if(C_UDMI(c,t,1)<0.0)
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*((-1.0)*C_UDMI(c,t,1)-C_UDMI(c_n,t,1))+C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*((-1.0)*C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								// }
								// else
								// {
								// C_UDMI(c_n,t,3)+=(dx/ds)*(C_UDMI(c,t,1)+C_UDMI(c_n,t,1))-C_UDMI(c_n,t,1);
								// C_UDMI(c_n,t,4)+=(dx/ds)*(C_UDMI(c,t,2)+C_UDMI(c_n,t,2))-C_UDMI(c_n,t,2);
								// }
								// }
							}

							
							if ((dx/ds) > 2.5)
							{
								Message("dx/ds is: %e for cell %i. deltat should be reduced to reduce the dx for the given velocity.\n", dx/ds, c);
							}
							
							// if ((c % 200) == 0)/*min<(DeltaNW[0]/DeltaNW[1]))*/
							// {
							// Message("dx/ds is: %e .\n", dx/ds);
							// }

#endif

#if RP_3D
							C_UDMI(c_n,t,8)+=1.0; /*number of neighbors*/
							if ((dx/ds)>=1.0)
							{
								C_UDMI(c_n,t,5)+=C_UDMI(c,t,2);
								C_UDMI(c_n,t,6)+=C_UDMI(c,t,3);
								C_UDMI(c_n,t,7)+=C_UDMI(c,t,4);

							}
							else
							{
								C_UDMI(c_n,t,5)+=C_UDMI(c_n,t,2);//(dx/ds)*(C_UDMI(c,t,2)-C_UDMI(c_n,t,2))+C_UDMI(c_n,t,2);
								C_UDMI(c_n,t,6)+=C_UDMI(c_n,t,3);//(dx/ds)*(C_UDMI(c,t,3)-C_UDMI(c_n,t,3))+C_UDMI(c_n,t,3);
								C_UDMI(c_n,t,7)+=C_UDMI(c_n,t,4);//(dx/ds)*(C_UDMI(c,t,4)-C_UDMI(c_n,t,4))+C_UDMI(c_n,t,4);
							}
							if ((dx/ds) > 2.5)
							{
								Message("dx/ds is: %e for cell %i. deltat should be reduced to reduce the dx for the given velocity.\n", dx/ds, c);
							}
#endif
						}
					}
				}
			}
			//Message("dx/ds is: %e for cell %i. \n ", dx/ds,c);
		}
		end_c_loop(c,t)
	}
	//Message("dx/ds is: %e for cell %i. ", dx/ds,c);
}

void Initial_condition()
{
	Domain *domain=Get_Domain(1);
	Thread *t;
	cell_t c;
	face_t f;
	real x[ND_ND];
	int i;
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
			C_CENTROID(x,c,t);
			
#if RP_2D
			C_UDMI(c,t,0)=0.0;//3.1416/2.0;
			Set_User_Memory_Name(0,"angle_from_x_axis");
			Set_User_Memory_Name(1,"directors_x_component");
			Set_User_Memory_Name(2,"directors_y_component");
			C_UDMI(c,t,1)=cos(C_UDMI(c,t,0)); 
			C_UDMI(c,t,2)=sin(C_UDMI(c,t,0)); 
#endif
			
#if RP_3D
				
				if (x[2]<0.01)
				{
					C_UDMI(c,t,2)=1.0;
					C_UDMI(c,t,3)=0.0;
					C_UDMI(c,t,4)=0.0;
				}
				else
				{
					C_UDMI(c,t,2)=0.0;
					C_UDMI(c,t,3)=0.0;
					C_UDMI(c,t,4)=1.0;
				}				
			
#endif
			
		}
		end_c_loop(c,t)
	}
}

void OrderParameter()
{
	Domain *domain=Get_Domain(1);
	Thread *t;
	cell_t c;
	face_t f;
//	real x[ND_ND];
	int i=1,j=1,k;
	real Pi=3.1416;
	real deltatheta=Pi/180.0;
	real theta=0.0,S=0.0;
	real ff[360];
	for(j=1;j<360;j++)
	 ff[j]=0.0;
	 
	 thread_loop_c(t,domain)  
	{
		begin_c_loop(c,t)
		{
//			C_CENTROID(x,c,t);
			
#if RP_2D
			if(C_UDMI(c,t,1)==0)C_UDMI(c,t,1)=0.00001;
			C_UDMI(c,t,0)=atan(C_UDMI(c,t,2)/C_UDMI(c,t,1));
#endif
			
#if RP_3D						
#endif	
		}
		end_c_loop(c,t)
	}
	 
	thread_loop_c(t,domain)
	{
		begin_c_loop(c,t)
		{
//			C_CENTROID(x,c,t);
			
#if RP_2D
//		i=1;
		for(theta=0.0;theta<=Pi;theta=theta+deltatheta)
		{
			if (C_UDMI(c,t,0)>=theta && C_UDMI(c,t,0)<(theta+deltatheta))
			{
				k=theta*180/Pi;
				ff[k+1]=ff[k+1]+1;
				i++;
				break;
			}
		}		

#endif
			
#if RP_3D
 				
#endif	
		}
		end_c_loop(c,t)
	}
	
 
	for(theta=0.0;theta<=Pi;theta=theta+deltatheta)
	{
		k=theta*180/Pi;
		ff[k+1]=ff[k+1]/i;
	}
	
//	thread_loop_c(t,domain)
//	{
//		begin_c_loop(c,t)
//		{
#if RP_2D
		j=1;
		for(theta=0.0;theta<=Pi;theta=theta+deltatheta)
		{
			k=theta*180/Pi;
			S=S+(1.0-3.0/2.0*pow(sin(theta),2))*ff[k+1];  
			j=j+1;
//			Message("i= %d, k= %d , j= %d , S= %e , P(j)= %e \n",i , k, j, S, ff[k+1]);
		}		
#endif
			
#if RP_3D
					
#endif	
//		}
//		end_c_loop(c,t)
//	}
	Message("The order parameter (S) is: %e, theta is: %e maximum k is: %d\n", S, theta, k);
}