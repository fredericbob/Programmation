package projet.service;

import projet.Configurations.JWTManager;

import projet.model.Role;
import projet.model.Utilisateur;
import projet.repository.UtilisateurRepository;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.Optional;
import java.util.UUID;

@Service
public class UtilisateurService {

    private final UtilisateurRepository utilisateurRepository;

    @Autowired
    private PasswordEncoder passwordEncoder;

    public UtilisateurService(UtilisateurRepository utilisateurRepository) {
        this.utilisateurRepository = utilisateurRepository;
    }

    public Optional<Utilisateur> findByEmail(String email) {
        return utilisateurRepository.findByEmail(email);
    }

    public String login(String email, String password) throws Exception {
        Utilisateur utilisateur = utilisateurRepository.findByEmail(email)
                .orElseThrow(() -> new Exception("Identifiants invalides"));

        if (utilisateur.isAccountLocked()) {
            throw new Exception("Compte bloquer. Veuillez réinitialiser votre mot de passe.");
        }

        if (!passwordEncoder.matches(password, utilisateur.getPassword())) {
            utilisateur.setFailedLoginAttempts(utilisateur.getFailedLoginAttempts() + 1);
            if (utilisateur.getFailedLoginAttempts() >= 3) {
                utilisateur.setAccountLocked(true);
            }
            utilisateurRepository.save(utilisateur);
            throw new Exception("Identifiants invalides");
        }

        utilisateur.setFailedLoginAttempts(0);
        utilisateur.setAccountLocked(false);
        utilisateurRepository.save(utilisateur);

        return JWTManager.generateToken(utilisateur);
    }

    public void resetFailedAttempts(String email) throws Exception {
        Utilisateur utilisateur = utilisateurRepository.findByEmail(email)
                .orElseThrow(() -> new Exception("Utilisateur non trouvé"));

        utilisateur.setFailedLoginAttempts(0);
        utilisateur.setAccountLocked(false);
        utilisateurRepository.save(utilisateur);
    }

    public Utilisateur save(Utilisateur utilisateur) {

        try {

            if (utilisateur.getEmail() == null || utilisateur.getPassword() == null) {
                throw new IllegalArgumentException("Tous les champs doivent être remplis.");
            }
            String validationToken = generateValidationToken();

            Utilisateur utilisateur1 = new Utilisateur();

            utilisateur.setValidationToken(validationToken);
            utilisateur.setValidated(false);

            utilisateur1.setEmail(utilisateur.getEmail());

            utilisateur1.setPassword(passwordEncoder.encode(utilisateur.getPassword()));
            utilisateur1.setRole(new Role(2));

            Utilisateur savedUtilisateur = utilisateurRepository.save(utilisateur1);

            return savedUtilisateur;
        } catch (Exception e) {
            throw new RuntimeException("Erreur lors de l'ajout de l'utilisateur : " + e.getMessage());
        }
    }

    public String generateValidationToken() {
        return UUID.randomUUID().toString();
    }

    public boolean validateUserByToken(String token) {
        Utilisateur user = utilisateurRepository.findByValidationToken(token); // Recherche par token
        if (user != null && !user.isValidated()) {
            user.setValidated(true); // Marquer l'utilisateur comme validé
            utilisateurRepository.save(user); // Sauvegarder
            return true;
        }
        return false; // Token invalide ou utilisateur déjà validé
    }

    public void resetEmail(String email) throws Exception {
        Utilisateur utilisateur = utilisateurRepository.findByEmail(email)
                .orElseThrow(() -> new Exception("Utilisateur non trouvé"));

        utilisateur.setFailedLoginAttempts(0);
        utilisateur.setAccountLocked(false);
        utilisateurRepository.save(utilisateur);
    }

}
