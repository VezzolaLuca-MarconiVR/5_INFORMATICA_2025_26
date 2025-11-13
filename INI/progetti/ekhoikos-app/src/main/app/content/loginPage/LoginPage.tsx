import React, { useState } from "react";

export default function LoginPage() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    // qui metti la tua logica di autenticazione
    alert(`Login con utente: ${username}, password: ${password}`);
  };

  return (
    <div className="center-both" style={{ width: "100%", height: "100%" }}>
      <div className="center-y" style={{ padding: "20" }}>
        <h1>Login</h1>
        <form
          onSubmit={handleSubmit}
          style={{ display: "flex", flexDirection: "column", maxWidth: "300" }}
        >
          <label>
            Username
            <input
              type="text"
              value={username}
              onChange={(e) => setUsername(e.target.value)}
              style={{ marginBottom: 10 }}
            />
          </label>
          <label>
            Password
            <input
              type="password"
              value={password}
              onChange={(e) => setPassword(e.target.value)}
              style={{ marginBottom: 10 }}
            />
          </label>
          <button type="submit">Accedi</button>
        </form>
      </div>
    </div>
  );
}
