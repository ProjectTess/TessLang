//
// Created by tess on 4/7/26.
//

#ifndef TESSLANG_TESSERROR_HXX
#define TESSLANG_TESSERROR_HXX

#include <string>

namespace tess
{
  namespace error
  {
    class TessError
    {
      protected:
        TessError() = default;
      public:
        virtual ~TessError() noexcept = default;
        virtual const char* message() const noexcept = 0;
    };
  }
}

#endif   // TESSLANG_TESSERROR_HXX
