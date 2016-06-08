//
//  Log.hpp
//  tests
//
//  Created by Derek Higgs on 6/7/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Log_hpp
#define Log_hpp

namespace kettle {
    namespace utils {
        /**
         * Prints a statement in a debug build.
         *
         * @param debug_level   The minimum value of DEBUG in order to print.
         * @param format        The format of the statement.
         * @param ...           Additional values to go into
         */
        void log(unsigned int debug_level, const char * format, ...);
        
        /**
         * Prints a statement in a debug build.
         *
         * @param format        The format of the statement.
         * @param ...           Additional values to go into
         */
        void log(const char * format, ...);
    } // namespace utils
} // namespace kettle

#endif /* Log_hpp */
