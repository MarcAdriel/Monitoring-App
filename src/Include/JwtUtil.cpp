#include "../Header/JwtUtil.h"

const string SECRET_KEY = "s2unkr8+1EZ3IGEPVYAldFfnPMsrwtC1cY2+De0OlmA=";
const string ISSUER = "auth_service";

string JwtUtil::GenerateToken(const string &email, const string &role) {
    auto token = jwt::create()
            .set_issuer("auth_service")
            .set_type("JWT")
            .set_payload_claim("email", jwt::claim(email))
            .set_payload_claim("role", jwt::claim(role))
            .sign(jwt::algorithm::hs256{SECRET_KEY});
    return token;
}

bool JwtUtil::VerifyToken(const std::string &token, std::string &role, std::string &email) {
    try {
        // Decode JWT token (DOES NOT verify signature yet)
        auto decoded = jwt::decode(token);

        // Create a verifier and enforce strict validation
        auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{SECRET_KEY})  // Ensure correct algorithm
                .with_issuer(ISSUER); // Ensure token is issued by our auth service

        // Verify the token - this checks the signature!
        verifier.verify(decoded);  // If signature is invalid, this will throw an exception

        // Extract required claims
        if (decoded.has_payload_claim("role")) {
            role = decoded.get_payload_claim("role").as_string();
        } else {
            std::cerr << "Missing role in token\n";
            return false;
        }

        if (decoded.has_payload_claim("email")) {
            email = decoded.get_payload_claim("email").as_string();
        } else {
            std::cerr << "Missing email in token\n";
            return false;
        }

        // Ensure the issuer is correct
        if (decoded.has_payload_claim("iss")) {
            std::string tokenIssuer = decoded.get_payload_claim("iss").as_string();
            if (tokenIssuer != ISSUER) {
                std::cerr << "Invalid issuer: " << tokenIssuer << std::endl;
                return false;
            }
        } else {
            std::cerr << "Missing issuer claim\n";
            return false;
        }

        return true; // Token is valid
    } catch (const jwt::error::token_verification_exception &e) {
        std::cerr << "Invalid JWT signature: " << e.what() << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "Token verification failed: " << e.what() << std::endl;
        return false;
    }
}

string JwtUtil::GetRoleFromToken(const string &token) {
    auto decoded = jwt::decode(token);
    return decoded.get_payload_claim("role").as_string();
}
