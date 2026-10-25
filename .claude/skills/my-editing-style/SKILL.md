---
name: my-editing-style
description: Edit raw talking-head footage into a vertical (9:16) TikTok / Reels / Shorts video in my house style - tight jump cuts, a big two-typeface hook title, word-synced captions with a blue italic-serif highlight word, and floating cards for the key things I mention. Use whenever I ask to edit a video, cut a clip, or "make this a TikTok".
---

# My editing style

Learned from five reference TikToks about editing with Claude (talking-head creators: george.automates, samdespo, justyn.ai, Brand Nat). The style is **talking head on the bottom half, graphics on the top half, never dead air.**

## Output spec

- 1080x1920, 30 fps, H.264 + AAC, `-movflags +faststart`.
- Length: whatever the content needs after cutting, usually 45-90 s.
- Loudness: normalise the final mix to **-14 LUFS integrated, -1 dBTP**.
- Keep a safe zone free of anything important: top 8% (TikTok search bar), bottom 15% (caption/handle area), right 12% (like/comment buttons).

## Workflow

1. **Ingest.** Raw footage goes in `raw/`, finished edits in `exports/`. Probe it with ffprobe. If it is landscape, crop to 9:16 centred on the face. If it is 60 fps, render at 30.
2. **Transcribe** with word-level timestamps: ElevenLabs Scribe (`ELEVENLABS_API_KEY` from the environment or `.env`, never hard-coded or committed), or a local Whisper if that is unavailable. Save it as `work/transcript.json`.
3. **Cut plan.** From the transcript, list every keep-range:
   - Remove silences longer than **0.25 s**. Leave about 0.06 s of air at each edge so words are not clipped.
   - Remove filler words ("um", "uh", "like," "you know"), false starts and repeated takes, keeping the **last** good take.
   - Target: no gap over 0.35 s anywhere in the final video.
4. **Storyboard first.** Before rendering, show me a table with these columns: time, what is said, framing (wide/punch), caption highlight word, card or graphic, SFX. For the hook, give **options A / B / C**. Wait for my OK.
5. **Build** the composition in HyperFrames (`/hyperframes`), with the cut footage as the base layer and captions, cards and titles as HTML/GSAP layers. Vendor GSAP and fonts locally if a CDN is unreachable.
6. **Check** with `npx hyperframes check --json` and `snapshot` at the hook, at each card and at the CTA. Look at the PNGs. Then render a `draft`, show me, and render `delivery` for the final.
7. Run a final audio pass in FFmpeg: `highpass=f=80, acompressor` (light), `loudnorm=I=-14:TP=-1:LRA=11`.

## Pacing and framing

- There is a visual change every **2-4 s**: a cut, a punch-in, a card entering, or a full-screen graphic.
- Two framings from the same take:
  - **Wide**: speaker fills the lower ~55% of the frame, with the head top at about 42% height.
  - **Punch-in**: scale 1.25-1.35x on the face for emphasis words, punchlines and the start of each new point. It is a hard cut, not a zoom ramp. Alternate wide and punch on every jump cut so cuts never look like glitches.
- Optional slow push (1.00 -> 1.04 over the shot) on long uninterrupted shots longer than 5 s.
- When a full-screen graphic takes over (1-3 s), blur the footage behind it (about 20 px) instead of cutting it away.

## Layout

- **Bottom half**: the speaker.
- **Top 40-45%**: reserved for the hook title, then floating cards. Graphics must never cover the face.

## Hook (0-2 s)

- A big title appears on the first word and builds word by word in step with the speech, filling the top half. Example: "I DIDN'T EDIT A *single* SECOND OF THIS".
- Mix the two typefaces: heavy sans in caps for most words, and **one or two words in the blue italic serif**.
- Add a visual proof where possible: a collage of results, a ticking timecode, a crossed-out competitor logo, or a screenshot.
- Optional promise pill shown under the title for 2-3 s: a rounded label with a blue fill and white bold sans, e.g. "5 Steps -> No Course".
- The title clears by about 2.5 s, and the first floating card takes its place.

## Captions

- **Position**: centred, with the baseline at about 72% of frame height (just under the chin on the wide shot).
- **Chunking**: **2-4 words** per caption, broken at natural phrase boundaries, never across a sentence end. Each chunk appears on its first word's start time and is replaced by the next chunk, so there is no gap.
- **Font**: Inter (or SF Pro) **Bold 600-700**, about 46 px at 1080 wide, white, in sentence case.
- **Background**: a rounded pill in `rgba(10,14,30,0.55)` with 10 px x 18 px padding and a 14 px radius.
- **Highlight**: one key word per chunk at most (a noun, number or tool name), set in **Instrument Serif Italic**, about 1.15x size, in the accent blue. Don't highlight filler.
- **Entrance**: 120 ms fade plus an 8 px rise. No bouncing or per-letter effects.

## Floating cards (for the key things I mention)

Trigger a card whenever I name a **tool, app, step number, file or folder, prompt, number or result**:

- Rounded white card (`#FFFFFF`, 22 px radius, shadow `0 18px 40px rgba(0,0,0,0.28)`), with its top edge about 10% down and a width of 70-86% of the frame.
- **Contents**: app logo plus name; a screenshot; a code or prompt snippet in a monospaced font on a light card with a "PROMPT  [Copy]" header; a folder tree; or a big number.
- **Enter**: on the exact word, scale 0.92 -> 1, fade in, and rise 24 px over 220 ms with ease `back.out(1.6)`. A soft "pop" SFX plays.
- **Hold**: until the next card, or about 2.5-4 s.
- **Exit**: 150 ms fade, or swap straight into the next card.
- **Lists** ("three tools", "five steps"): show one card with numbered icons that light up one by one as I say them.
- Step headers: "Step 1: *Claude Code*", with the label in sans and the name in the blue italic serif, plus small sparkle accents.
- If I haven't supplied a screenshot, build the card from a logo and text, or ask me for the image. **Never invent a fake UI** that pretends to be a real product screen.

## Typography and colour

| Role | Font | Colour |
| --- | --- | --- |
| Hook / titles | Inter Black / Extra Bold, caps | `#F5F7FF` |
| Accent words | **Instrument Serif Italic** | accent blue `#6EA8FF` (on dark), `#2F6BFF` (on white cards) |
| Captions | Inter Bold | `#FFFFFF` |
| Card body | Inter Medium | `#111827` / muted `#6B7280` |
| Code / prompts | JetBrains Mono | `#111827`, highlights `#FFE58A` |

- Use one accent colour per video (blue). Don't add a second accent.
- **Colour grade**: natural, with slight warmth on skin and a small contrast lift. In FFmpeg: `eq=contrast=1.05:saturation=1.06, colorbalance=rs=0.02:bs=-0.01`. No heavy LUTs. A subtle vignette is optional.

## Sound

- **Voice-first, with no music by default** (the references are voice only).
- **SFX**: a soft pop on card entrances, a short whoosh on full-screen graphic transitions, and an occasional tick or typing sound on text reveals. Keep them **-18 to -22 dB under the voice**, short, and never on every cut.
- **Optional music**, only if I ask: a lo-fi or minimal electronic bed at about -30 LUFS, ducked another 6 dB under speech, fading out on the CTA.

## Ending (last 3-5 s)

- **CTA**: "Comment **WORD** and I'll send you the walkthrough". Show it as a fake-but-generic comment bubble (avatar circle plus the word) that types in. Ask me for the WORD each video; if I don't say, use **GUIDE**.
- Finish with a small follow card (avatar, name, "Follow") for the final second. No outro music sting.

## Don'ts

- No captions over the face, no full-sentence subtitle blocks, no rainbow or multi-colour captions.
- No cut on a mid-word frame, and no jump cut that keeps the same framing twice in a row.
- No graphic in the TikTok UI safe zones.
- Never commit API keys, raw footage or renders to git.
