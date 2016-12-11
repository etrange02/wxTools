#ifndef SYSTEM_H
#define SYSTEM_H

#include <wx/wx.h>

namespace tools
{
    namespace system
    {
        class System
        {
            public:
                /** Default constructor */
                System();
                /** Default destructor */
                virtual ~System();

                static wxString getUnauthorizedCharacterFile();
                static bool createShortcut(const wxString& shortcut, const wxString& filename);

            protected:

            private:
        };
    }
}


#endif // SYSTEM_H
