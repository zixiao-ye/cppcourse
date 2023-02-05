#include "monitor.h"

#include<iostream>
#include <thread>



FileMonitor::FileMonitor(const std::string &targetpath,
                         std::chrono::milliseconds interval,
                         const std::string &logfilename)
    : logger{logfilename}
    , interval{interval}
    , targetpath{targetpath}            
{}

// Monitor the targetpath for changes and pass information to the logger in case of differences
void FileMonitor::start(std::chrono::seconds timeout) {
    std::chrono::time_point<std::chrono::system_clock> flag, end;
    flag = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now() + timeout;

    while(std::chrono::system_clock::now() < end) 
    {
        if (std::chrono::system_clock::now() > flag)
        {
            for (auto const& entry : fs::recursive_directory_iterator(targetpath))
            {
                std::string p = entry.path();
                //std::cout<<p<<std::endl;
                if (m.find(p) == m.end())
                {
                    logger.log(p, status::added);
                    m.insert({p, fs::last_write_time(p)});
                }else{
                    if(m[p] != fs::last_write_time(p)){
                        logger.log(p, status::changed);
                        m[p] = fs::last_write_time(p);
                    }
                }
                
            }
            for (auto& it : m)
            {
                if (!fs::exists(it.first))
                {
                    logger.log(it.first, status::removed);
                    m.erase(it.first);
                }
                
            }
            flag += interval;
            if (end - std::chrono::system_clock::now() < interval)
                break;
            
        }
    }
    //std::this_thread::sleep_for(std::chrono::microseconds(interval));
}
