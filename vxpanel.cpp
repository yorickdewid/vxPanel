#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/rpc_json.h>
#include <fstream>
#include <string>
#include <sstream>


class json_service : public cppcms::rpc::json_rpc_server {
public:
    json_service(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
    {
    	bind("sum",cppcms::rpc::json_method(&json_service::sum,this),method_role);
    	bind("div",cppcms::rpc::json_method(&json_service::div,this),method_role);
    	bind("notify",cppcms::rpc::json_method(&json_service::notify,this),notification_role);
    	bind("both",cppcms::rpc::json_method(&json_service::both,this));
        bind("system_uptime",cppcms::rpc::json_method(&json_service::system_uptime,this),method_role);
    }
    void sum(int x,int y)
    {
        std::cout << "Sum Called" << std::endl;
    	return_result(x+y);
    }
    void div(int x,int y)
    {
        std::cout << "Div Called" << std::endl;
    	if(y==0)
    		return_error("Division by zero");
    	else
    		return_result(x/y);
    }
    void notify(std::string msg)
    {
        std::cout << "We got notification " << msg << std::endl;
    }
    void both(std::string msg)
    {
    	if(notification())
            std::cout << "We got notification " << msg << std::endl;
    	else
    	    return_result("call:"+msg);
    }
    void system_uptime(){
        std::ifstream uptime;
        std::string result;
        uptime.open ("/proc/uptime");
        if (uptime.is_open()) { 
            for( std::string line; getline( uptime, line ); )
            {
                std::size_t pos = line.find(" ");
                std::string s = line.substr (0,pos);//second number is idle time
                result = format_uptime(s);
            }
        }
        uptime.close();
        return_result(result);
    }

private:
    std::string format_uptime(std::string sec){
        long seconds = atol(sec.c_str());
        unsigned int days = seconds / 86400;
        seconds = seconds % 86400;
        unsigned int hours = seconds / 3600;
        seconds = seconds % 3600;
        unsigned int mins = seconds / 60;
        seconds = seconds % 60;
        unsigned int secs = seconds;
        std::ostringstream os;
        os << "Days " << days << "," << hours << ":" << mins << ":" << secs;
        std::string s = os.str();
        return s;
    }
};



int main(int argc,char **argv)
{
    try {
        std::cout << "Starting vxPanel" << std::endl;
    	cppcms::service srv(argc,argv);
    	srv.applications_pool().mount(cppcms::applications_factory<json_service>());
    	srv.run();
    }
    catch(std::exception const &e) {
    	std::cerr << e.what() << std::endl;
    	return 1;
    }
    return 0;
}
