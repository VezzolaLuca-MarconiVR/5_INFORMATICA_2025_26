import React, { useEffect, useState } from "react";

/* Config */
const STORAGE_KEY = "theme-preference";
const THEME_DARK = "dark";
const THEME_LIGHT = "light";

/* Helper DOM e storage */
function readStoredTheme() {
  try {
    const v = localStorage.getItem(STORAGE_KEY);
    if (v === THEME_DARK || v === THEME_LIGHT) return v;
  } catch (e) {}
  return null;
}
function storeTheme(theme) {
  try {
    localStorage.setItem(STORAGE_KEY, theme);
  } catch (e) {}
}
function systemPrefersDark() {
  return (
    typeof window !== "undefined" &&
    window.matchMedia?.("(prefers-color-scheme: dark)").matches
  );
}
function applyThemeToDocument(theme) {
  const root = document.documentElement;
  if (theme === THEME_DARK) root.classList.add("dark");
  else root.classList.remove("dark");
}

/* Componente unico che gestisce tutto */
export default function ToggleTheme({ initial = null }) {
  const initialTheme = (() => {
    if (initial === THEME_DARK || initial === THEME_LIGHT) return initial;
    const stored = readStoredTheme();
    if (stored) return stored;
    return systemPrefersDark() ? THEME_DARK : THEME_LIGHT;
  })();

  const [theme, setTheme] = useState(initialTheme);

  /* Applica tema su mount e quando cambia */
  useEffect(() => {
    applyThemeToDocument(theme);
    storeTheme(theme);
  }, [theme]);

  /* Sincronizza con preferenza di sistema se l'utente non ha scelto esplicitamente */
  useEffect(() => {
    const stored = readStoredTheme();
    if (stored) return;
    const mq = window.matchMedia?.("(prefers-color-scheme: dark)");
    if (!mq) return;
    const handler = (e) => setTheme(e.matches ? THEME_DARK : THEME_LIGHT);
    mq.addEventListener?.("change", handler);
    return () => mq.removeEventListener?.("change", handler);
  }, []);

  const toggle = () =>
    setTheme((t) => (t === THEME_DARK ? THEME_LIGHT : THEME_DARK));

  return (
    <button
      className="theme-toggle"
      onClick={toggle}
      aria-pressed={theme === THEME_DARK}
      title={theme === THEME_DARK ? "Passa a light" : "Passa a dark"}
      style={{
        padding: ".4rem .8rem",
        borderRadius: 6,
        border: "1px solid var(--border)",
        background: "var(--bg-light)",
        color: "var(--text)",
        cursor: "pointer",
      }}
    >
      {theme === THEME_DARK ? "Light mode" : "Dark mode"}
    </button>
  );
}
