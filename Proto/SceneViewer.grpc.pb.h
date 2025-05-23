// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: SceneViewer.proto
#ifndef GRPC_SceneViewer_2eproto__INCLUDED
#define GRPC_SceneViewer_2eproto__INCLUDED

#include "SceneViewer.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>
#include <grpcpp/ports_def.inc>

class SceneStreamerService final {
 public:
  static constexpr char const* service_full_name() {
    return "SceneStreamerService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderInterface< ::FileChunkReply>> SendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::FileChunkReply>>(SendSceneRequestRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>> AsyncSendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>>(AsyncSendSceneRequestRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>> PrepareAsyncSendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>>(PrepareAsyncSendSceneRequestRaw(context, request, cq));
    }
    virtual ::grpc::Status RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::SceneFilepathsReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>> AsyncRequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>>(AsyncRequestSceneFilePathsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>> PrepareAsyncRequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>>(PrepareAsyncRequestSceneFilePathsRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void SendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest* request, ::grpc::ClientReadReactor< ::FileChunkReply>* reactor) = 0;
      virtual void RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientReaderInterface< ::FileChunkReply>* SendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>* AsyncSendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::FileChunkReply>* PrepareAsyncSendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>* AsyncRequestSceneFilePathsRaw(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::SceneFilepathsReply>* PrepareAsyncRequestSceneFilePathsRaw(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReader< ::FileChunkReply>> SendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::FileChunkReply>>(SendSceneRequestRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::FileChunkReply>> AsyncSendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::FileChunkReply>>(AsyncSendSceneRequestRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::FileChunkReply>> PrepareAsyncSendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::FileChunkReply>>(PrepareAsyncSendSceneRequestRaw(context, request, cq));
    }
    ::grpc::Status RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::SceneFilepathsReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>> AsyncRequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>>(AsyncRequestSceneFilePathsRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>> PrepareAsyncRequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>>(PrepareAsyncRequestSceneFilePathsRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void SendSceneRequest(::grpc::ClientContext* context, const ::SceneRequest* request, ::grpc::ClientReadReactor< ::FileChunkReply>* reactor) override;
      void RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response, std::function<void(::grpc::Status)>) override;
      void RequestSceneFilePaths(::grpc::ClientContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientReader< ::FileChunkReply>* SendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request) override;
    ::grpc::ClientAsyncReader< ::FileChunkReply>* AsyncSendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::FileChunkReply>* PrepareAsyncSendSceneRequestRaw(::grpc::ClientContext* context, const ::SceneRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>* AsyncRequestSceneFilePathsRaw(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::SceneFilepathsReply>* PrepareAsyncRequestSceneFilePathsRaw(::grpc::ClientContext* context, const ::EmptyMsg& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SendSceneRequest_;
    const ::grpc::internal::RpcMethod rpcmethod_RequestSceneFilePaths_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SendSceneRequest(::grpc::ServerContext* context, const ::SceneRequest* request, ::grpc::ServerWriter< ::FileChunkReply>* writer);
    virtual ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendSceneRequest(::grpc::ServerContext* context, ::SceneRequest* request, ::grpc::ServerAsyncWriter< ::FileChunkReply>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRequestSceneFilePaths(::grpc::ServerContext* context, ::EmptyMsg* request, ::grpc::ServerAsyncResponseWriter< ::SceneFilepathsReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SendSceneRequest<WithAsyncMethod_RequestSceneFilePaths<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::SceneRequest, ::FileChunkReply>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::SceneRequest* request) { return this->SendSceneRequest(context, request); }));
    }
    ~WithCallbackMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::FileChunkReply>* SendSceneRequest(
      ::grpc::CallbackServerContext* /*context*/, const ::SceneRequest* /*request*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::EmptyMsg, ::SceneFilepathsReply>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::EmptyMsg* request, ::SceneFilepathsReply* response) { return this->RequestSceneFilePaths(context, request, response); }));}
    void SetMessageAllocatorFor_RequestSceneFilePaths(
        ::grpc::MessageAllocator< ::EmptyMsg, ::SceneFilepathsReply>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::EmptyMsg, ::SceneFilepathsReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* RequestSceneFilePaths(
      ::grpc::CallbackServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_SendSceneRequest<WithCallbackMethod_RequestSceneFilePaths<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSendSceneRequest(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRequestSceneFilePaths(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const::grpc::ByteBuffer* request) { return this->SendSceneRequest(context, request); }));
    }
    ~WithRawCallbackMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* SendSceneRequest(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->RequestSceneFilePaths(context, request, response); }));
    }
    ~WithRawCallbackMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* RequestSceneFilePaths(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_RequestSceneFilePaths : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_RequestSceneFilePaths() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::EmptyMsg, ::SceneFilepathsReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::EmptyMsg, ::SceneFilepathsReply>* streamer) {
                       return this->StreamedRequestSceneFilePaths(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_RequestSceneFilePaths() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status RequestSceneFilePaths(::grpc::ServerContext* /*context*/, const ::EmptyMsg* /*request*/, ::SceneFilepathsReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedRequestSceneFilePaths(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::EmptyMsg,::SceneFilepathsReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_RequestSceneFilePaths<Service > StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_SendSceneRequest : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_SendSceneRequest() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::SceneRequest, ::FileChunkReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerSplitStreamer<
                     ::SceneRequest, ::FileChunkReply>* streamer) {
                       return this->StreamedSendSceneRequest(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_SendSceneRequest() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SendSceneRequest(::grpc::ServerContext* /*context*/, const ::SceneRequest* /*request*/, ::grpc::ServerWriter< ::FileChunkReply>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedSendSceneRequest(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::SceneRequest,::FileChunkReply>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_SendSceneRequest<Service > SplitStreamedService;
  typedef WithSplitStreamingMethod_SendSceneRequest<WithStreamedUnaryMethod_RequestSceneFilePaths<Service > > StreamedService;
};


#include <grpcpp/ports_undef.inc>
#endif  // GRPC_SceneViewer_2eproto__INCLUDED
