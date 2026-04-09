//
// Created by tess on 4/2/26.
//

#ifndef TESSLANG_IBASENODE_HXX
#define TESSLANG_IBASENODE_HXX

namespace tess
{
  namespace parser
  {
    namespace node
    {

      class IASTVisitor;

      class IBaseNode
      {
        protected:
          IBaseNode() = default;

        public:
          virtual ~IBaseNode() = default;
          virtual void accept(IASTVisitor& visitor) = 0;
      };

    }   // namespace node
  }   // namespace parser
}   // namespace tess

#endif   // TESSLANG_IBASENODE_HXX