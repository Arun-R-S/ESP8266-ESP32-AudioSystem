#include "core/SystemManager.h"
#include "ui/web/fields/HtmlTags.h"
#include "SystemElements.h"
#include "utils/StringUtils.h"

String SystemElements::UpTime(bool isLiveElement) {
    if(isLiveElement)
    {
        return HtmlSpan(SystemManager::GetUptimeString(),HtmlAttr("livestatuscmd","sys=upt"));
    }
    else{
        return HtmlSpan(SystemManager::GetUptimeString());
    }
}

String SystemElements::RamUsage(bool isLiveElement) {
    if(isLiveElement)
    {
        return HtmlSpan(StringUtils::ConvertByteUnits(double(SystemManager::GetUsedRam()),"B","KB",2,true)
        ,HtmlAttr("livestatuscmd","sys=uram"));
    }
    else{
        return HtmlSpan(StringUtils::ConvertByteUnits(double(SystemManager::GetUsedRam()),"B","KB",2,true));
    }
}
