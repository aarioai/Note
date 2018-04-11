extension Conf {
    struct URL {
        private struct host {
            static let a = "http://192.168.1.103/"
        }
        
        static let requestJSON = host.a + "swift/"
        
        static let uploadFile = host.a + "swift/uploadFile.php"
        
        
        struct UploadFile {
            static let url = Conf.URL.host.a + "swift/uploadFile.php"
            static let methods: HttpMethod = .POST
            struct Params {
                let accessToken = URLParamStruct<String>(key: "access_token", required: true, regexp: nil, defaultValue: nil)
            }
            struct Result {
                
            }
        }
        
        enum AccessTokenGrantType: String {
            case ClientCredentials = "client_credentials"
            case LongLivedToken = "long_lived_token"
        }
        
        struct AccessToken {
            static let url = Conf.URL.host.a + "base/Aaphp/example/public/?c=oauth&a=access_token"
            static let methods: HttpMethod = .GET
            struct Params {
                let appID = URLParamStruct<String>(key: "app_id", required: true)
                let appSecret = URLParamStruct<String>(key: "app_secret", required: true, regexp: nil, defaultValue: nil)
                let grantType = URLParamStruct<AccessTokenGrantType>(key: "grant_type", required: true, regexp: nil, defaultValue: .ClientCredentials)
            }
            struct Result {
                
            }
        }
        
        
        
        
        
        
    }
}