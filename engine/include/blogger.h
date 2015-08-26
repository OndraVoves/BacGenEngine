/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef BLOGGER_H
#define BLOGGER_H

#include <BoxE/BoxECore>

#define BGE_LOGGER_INFO( logger_ptr, class_name, fce_name, msg )\
    if( logger_ptr ) {\
        logger_ptr->info( BoxE::Core::BAsciiString( "%1::%2() : %3").replace( "%1", BoxE::Core::BAsciiString( class_name ) )\
                          .replace( "%2", BoxE::Core::BAsciiString( fce_name   ) )\
                          .replace( "%3", BoxE::Core::BAsciiString( msg      ) ) );\
    }

#define BGE_LOGGER_WARNING( logger_ptr, class_name, fce_name, msg )\
    if( logger_ptr ) {\
        logger_ptr->warning( BoxE::Core::BAsciiString( "%1::%2() : %3").replace( "%1", BoxE::Core::BAsciiString( class_name ) )\
                             .replace( "%2", BoxE::Core::BAsciiString( fce_name   ) )\
                             .replace( "%3", BoxE::Core::BAsciiString( msg        ) ) );\
    }

#define BGE_LOGGER_ERROR( logger_ptr, class_name, fce_name, msg )\
    if( logger_ptr ) {\
        logger_ptr->error( BoxE::Core::BAsciiString( "%1::%2() : %3").replace( "%1", BoxE::Core::BAsciiString( class_name ) )\
                           .replace( "%2", BoxE::Core::BAsciiString( fce_name   ) )\
                           .replace( "%3", BoxE::Core::BAsciiString( msg        ) ) );\
    }

#define BGE_LOGGER_DEBUG( logger_ptr, class_name, fce_name, msg )\
    if( logger_ptr ) {\
        logger_ptr->debug( BoxE::Core::BAsciiString( "%1::%2() : %3").replace( "%1", BoxE::Core::BAsciiString( class_name ) )\
                           .replace( "%2", BoxE::Core::BAsciiString( fce_name   ) )\
                           .replace( "%3", BoxE::Core::BAsciiString( msg        ) ) );\
    }

namespace BackGenEngine {
    /*!
     * Logger class.
     */
    class BLogger {
        public:
            /*!
             * Constructor.
             */
            BLogger();

            /*!
             * Destructor.
             */
            virtual ~BLogger();

            /*!
             * Information.
             * \param info Message.
             */
            virtual void info ( const BoxE::Core::BAsciiString &info ) const;

            /*!
             * Warning.
             * \param warning Message.
             */
            virtual void warning ( const BoxE::Core::BAsciiString &warning ) const;

            /*!
             * Error
             * \param error Message.
             */
            virtual void error ( const BoxE::Core::BAsciiString &error ) const;

            /*!
             * Debug.
             * \param debug Message.
             */
            virtual void debug ( const BoxE::Core::BAsciiString &debug ) const;
    };

}

#endif // BLOGGER_H
