# Muon Detection Experiment

This repository contains resources and documentation for a physics experiment aimed at detecting cosmic muons and measuring their lifetime using scintillators and Silicon Photomultipliers (SiPMs).

---

# Muon Lifetime Measurement Laboratory

## Abstract
This laboratory aims to estimate the mean lifetime of the muon (τμ) via its dominant decay channel:

**μ⁻ → e⁻ + ν̅ₑ + νμ**

The experimental setup uses plastic scintillators, photomultiplier tubes (PMTs), and NIM/VME electronics to detect cosmic muons and measure their decay times.

---

## Objectives
- Measure the muon lifetime (τμ) using cosmic ray muons.
- Validate the exponential decay law and relativistic time dilation.
- Compare experimental results with the PDG reference value.

---

## Experimental Setup
- **Scintillators**: 12 plastic scintillators arranged in 3 planes (A, B, C).
- **Iron Absorber**: Stops incoming muons between B and C planes.
- **Detectors**: PMTs coupled to scintillators.
- **Electronics**: NIM & VME crates, logic units, discriminators, dual timers, delay modules.
- **DAQ**: Flash ADC (CAEN v1720), CAENScope software, data analyzed with ROOT.

---

## Procedure Summary

### 1. Scintillator Efficiency
- Triple coincidence method used to estimate B1 efficiency:

** εB = NABC / NAC**
- Measurements performed across 25 voltage settings.
- Fitted with an error function (Gaussian approximation).
- Optimal voltage range for B1: **1500V–1800V**, with εB ≈ 0.8.

### 2. Coincidence Logic & Trigger
- **START**: A ∩ B ∩ ¬C — muon enters and stops in the iron.
- **STOP1**: A ∩ B ∩ G — decay particle exits upward.
- **STOP2**: C ∩ G — decay particle exits downward.
- **Trigger**: OR(STOP1, STOP2), with backward readout enabled.
- **Gate Width**: 10 µs, delayed by 85.5 ns to prevent false triggers.

### 3. Data Acquisition
- Flash ADC samples at 250 MSa/s (4 ns resolution), 12-bit precision.
- Signals converted to digital and stored (8192 samples per event).
- Analysis identifies START/STOP signals and computes time differences.

### 4. Data Analysis
- Events analyzed using ROOT framework.
- Lifetime calculated as time between START and STOP signals.
- Histogram fitted with:
** N(t) = p₀ · exp(−t/p₁) + p₂**

- Extracted lifetime:
**  τμ = 2113 ± 58 (stat) ± 26 (syst) ns** 

![Exponential fit](images/fit_esponenziale_1500bins.png)
*Exponential fit of data to calculate the muon lifetime. * 

---

## Conclusion
- The measured value is consistent with the PDG reference value (~2197 ns).
- STOP1 gives more reliable results due to dual-plane coincidence.
- STOP2 affected by background noise and geometric uncertainty.
- Confirms the expected exponential decay law and relativistic effects in cosmic muons.

---

## References
1. Particle Data Group, *Review of Particle Physics*, Phys. Rev. D 110, 030001 (2024).  
2. CAEN – Modular Pulse Processing Electronics: https://www.caen.it  
3. W.R. Leo, *Techniques for Nuclear and Particle Physics Experiments*, Springer (1994).  
4. Agilent U1241B Voltmeter Specifications  
5. G. D'Agostini, *Bayesian Reasoning in Data Analysis*, World Scientific (2003)
---

## 💡 Scintillators

Scintillators are materials that emit light (photons) when they are excited by ionizing radiation, such as when a muon passes through them. These materials are essential in detecting the passage of muons in our setup.




- Common materials: plastic or inorganic crystals (e.g., NaI(Tl))
- Emit photons in response to charged particles
- Coupled to light sensors (e.g., SiPMs) for readout

---

## 📷 Silicon Photomultipliers (SiPM)

SiPMs are highly sensitive light detectors used to detect the small flashes of light produced by scintillators. They are compact, solid-state devices with excellent timing resolution.


- Operate in Geiger mode to detect single photons
- Used for timing and energy measurements
- Ideal for portable or compact detector systems

---

## 📁 Contents

- `/src`: source code for data acquisition and analysis
- `/docs`: detailed documentation and references
- `/images`: high-resolution versions of figures and experimental setup

---

## 🧪 Authors & Contributions

This project is maintained by a group of physics students and educators passionate about particle detection. Contributions and feedback are welcome!

